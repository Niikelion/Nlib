#ifndef MTYPE_H_INCLUDED
#define MTYPE_H_INCLUDED

#include <nlib/utility/reference.h>

#include <functional>
#include <typeindex>
#include <memory>
#include <map>
#include <type_traits>
#include <cstring>
#include <exception>

#ifndef UNSAFE
#define UNSAFE
#endif // UNSAFE

namespace Nlib
{
    /**
    * \class mt_exception
    * \brief Multitype exceptions base.
    *
    * Multitype exception class. Every Mtype exception inherits from it.
    */
    class mt_exception: public std::exception
    {
    public:
        /**
        * @return Return error code string.
        */
        virtual const char* what() const noexcept
        {
            return "Mtype exception";
        }

        /**
        * \brief Default destructor.
        */
        virtual ~mt_exception() = default;
    };

    /**
    * \class mt_exception_any
    * \brief Any exception.
    *
    * Exception of unspecified type.
    */
    class mt_exception_any: public mt_exception
    {
    protected:
        const std::string _err;
    public:
        /**
        * @return Returns error string passed in constructor.
        */
        virtual const char* what() const noexcept
        {
            static const std::string prefix = "Mtype exception: ";
            return (prefix+_err).c_str();
        }

        mt_exception_any(const std::string& err) :_err(err) {/**/}

        mt_exception_any():_err("") {/**/}
        mt_exception_any(const mt_exception_any& target) :_err(target._err) {/**/}
        mt_exception_any(mt_exception_any&& target) noexcept :_err(std::move(target._err)) {/**/}

        virtual ~mt_exception_any() = default;
    };

    /**
    * \class mt_missing_func
    * \brief Missing function exception.
    *
    * Exception indicates that Mtype was unable to find function when it was necessary.
    */
    class mt_missing_func: public mt_exception
    {
    public:
        /**
        * @copydoc mt_exception::what()
        */
        virtual const char* what() const noexcept
        {
            return "Mtype exception: missing function";
        }
        virtual ~mt_missing_func() = default;
    };

    /**
    * \class mt_missing_delete
    * \brief Missing delete function exception
    *
    * Exception indicates that Mtype was unable to find delete function when it was necessary.
    */
    class mt_missing_delete: public mt_missing_func
    {
    public:
        /**
        * @copydoc mt_exception::what()
        */
        virtual const char* what() const noexcept
        {
            return "Mtype critical exception: memory leak occurred because of missing delete function";
        }
        virtual ~mt_missing_delete() = default;
    };

    /**
    * \class mt_missing_copy
    * \brief Missing copy function exception.
    *
    * Exception indicates that Mtype was unable to find copy function when it was necessary.
    */
    class mt_missing_copy: public mt_missing_func
    {
    public:
        /**
        * @copydoc mt_exception::what()
        */
        virtual const char* what() const noexcept
        {
            return "Mtype exception: missing copy function";
        }

        mt_missing_copy() = default;
        mt_missing_copy(const mt_missing_copy&) = default;
        mt_missing_copy(mt_missing_copy&&) noexcept = default;

        virtual ~mt_missing_copy();
    };

    /**
    * \class mt_missing_cast
    * \brief Missing cast function exception.
    *
    * Exception indicates that Mtype was unable to find cast function when it was necessary.
    */
    class mt_missing_cast: public mt_missing_func
    {
    public:
        /**
        * @copydoc mt_exception::what()
        */
        virtual const char* what() const noexcept
        {
            return "Mtype exception: missing cast function";
        }

        mt_missing_cast() = default;
        mt_missing_cast(const mt_missing_cast&) = default;
        mt_missing_cast(mt_missing_cast&&) noexcept = default;

        virtual ~mt_missing_cast();
    };

    /**
    * \class Mtype
    * \brief Class designed to store single object of any type.
    *
    * Mtype has built-in container and resizes it only when needed space is bigger than current buffer.<br>
    * Is also provides simple type check and protects the value inside storage from wrong usage.
    */
    class Mtype
    {
    protected:

        template<typename B>static void def_del_func(void* const& data)
        {
            reinterpret_cast<B*>(data)->~B();
        }
        template<typename B>static void* def_copy_func(void* data)
        {
            return reinterpret_cast<void*>( new B( *reinterpret_cast<B*>(data) ) );
        }
        template<typename B,typename T>static void* def_cast_func(void*& data,Mtype& parent,const bool& recast)
        {
            if (recast)
            {
                parent.set<T>( static_cast<T>( *reinterpret_cast<B*>(data) ) );

                return data;
            }
            return reinterpret_cast<void*>( new T( static_cast<T>( *reinterpret_cast<B*>(data) ) ) );
        }


        struct TempSpecifiers
        {
        public:
            typedef void(*tmp_del_func)(void* const&);
            typedef void*(*tmp_copy_func)(void* const&);
            typedef void(*tmp_cast_func)(void* &,const bool&);

            std::map<std::type_index,std::function<void(void* const&)> >                                            tmp_del;
            std::map<std::type_index,std::function<void*(void* const&)> >                                           tmp_copy;
            std::map<std::pair<std::type_index,std::type_index>,std::function<void*(void* &,Mtype&,const bool&)> >  tmp_cast;

            TempSpecifiers() = default;
            TempSpecifiers(const TempSpecifiers&) = default;
            TempSpecifiers(TempSpecifiers&&) noexcept;
        };

        static std::type_index __voidId;

        static TempSpecifiers globalTmpSpec;
        std::shared_ptr<TempSpecifiers> localTmpSpec;

        std::type_index _guard;
        char* _buffer;
        size_t _size;
        void* _storage;
    public:
        const std::type_index& type; /**< \brief Type of stored item or typeid(void) if empty. */

        /**
        * \brief Gets available delete function.
        * @param id Id of type.
        * @param global Disables local function search when set to true.
        * @return function that deletes object of given type if found.
        */
        std::function<void(void* const&)> getDelFunc(const std::type_index& id,const bool& global=false)const
        {
            thread_local std::map<std::type_index,std::function<void(void* const&)> >::iterator func;
            if (!global && static_cast<bool>(localTmpSpec) == true && (func = localTmpSpec->tmp_del.find(id)) != localTmpSpec->tmp_del.end())
            {
                return func->second;
            }
            if ((func = globalTmpSpec.tmp_del.find(id)) != globalTmpSpec.tmp_del.end())
            {
                return func->second;
            }
            return std::move(std::function<void(void* const&)>());
        }

        /**
        * \brief Gets available copy function.
        * @param id Id of type.
        * @param global Disables local function search when set to true.
        * @return function that copies object of given type if found.
        */
        std::function<void*(void* const&)> getCopyFunc(const std::type_index& id,const bool& global=false)const
        {
            thread_local std::map<std::type_index,std::function<void*(void* const&)> >::iterator func;
            if (!global && static_cast<bool>(localTmpSpec) == true && (func = localTmpSpec->tmp_copy.find(id)) != localTmpSpec->tmp_copy.end())
            {
                return func->second;
            }
            if ((func = globalTmpSpec.tmp_copy.find(id)) != globalTmpSpec.tmp_copy.end())
            {
                return func->second;
            }
            return std::move(std::function<void*(void* const&)>());
        }

        /**
        * \brief Gets available cast function.
        * @param base Id of base type.
        * @param id Id of type to cast to.
        * @param global Disables local function search when set to true.
        * @return function that casts object of given base type to type if found.
        */
        std::function<void*(void* &,Mtype&,const bool&)> getCastFunc(const std::type_index& base,const std::type_index& id,const bool& global=false)const
        {
            thread_local std::map<std::pair<std::type_index,std::type_index>,std::function<void*(void* &,Mtype&,const bool&)> >::iterator func;
            if (!global && static_cast<bool>(localTmpSpec) == true && (func = localTmpSpec->tmp_cast.find(std::make_pair(base,id))) != localTmpSpec->tmp_cast.end())
            {
                return func->second;
            }
            if ((func = globalTmpSpec.tmp_cast.find(std::make_pair(base,id))) != globalTmpSpec.tmp_cast.end())
            {
                return func->second;
            }
            return std::move(std::function<void*(void* &,Mtype&,const bool&)>());
        }

        /**
        * \brief Add delete function for \a id type.
        * @param id Type id.
        * @param func Delete function.
        * @param global Function will be added globally if set to true.
        */
        void setDelFunc(const std::type_index& id,std::function<void(void* const&)>func ,const bool& global=false)
        {
            if (global)
            {
                globalTmpSpec.tmp_del.insert(std::make_pair(id,func));
            }
            else if (static_cast<bool>(localTmpSpec))
            {
                localTmpSpec->tmp_del.insert(std::make_pair(id,func));
            }
        }

        /**
        * \brief Add copy function for \a id type.
        * @param id Type id.
        * @param func Copy function.
        * @param global Function will be added globally if set to true.
        */
        void setCopyFunc(const std::type_index& id,std::function<void*(void* const&)>func ,const bool& global=false)
        {
            if (global)
            {
                globalTmpSpec.tmp_copy.insert(std::make_pair(id,func));
            }
            else if (static_cast<bool>(localTmpSpec))
            {
                localTmpSpec->tmp_copy.insert(std::make_pair(id,func));
            }
        }

        /**
        * \brief Add cast function from \a base to \a id.
        * @param base Base type id.
        * @param id Type id.
        * @param func Cast function.
        * @param global Function will be added globally if set to true.
        */
        void setCastFunc(const std::type_index& base,const std::type_index& id,std::function<void*(void* &,Mtype& ,const bool&)>func ,const bool& global=false)
        {
            if (global)
            {
                globalTmpSpec.tmp_cast.insert(std::make_pair(std::make_pair(base,id),func));
            }
            else if (static_cast<bool>(localTmpSpec))
            {
                localTmpSpec->tmp_cast.insert(std::make_pair(std::make_pair(base,id),func));
            }
        }

        /**
        * \brief Prepares delete and copy functions for given type.
        * @tparam T base type
        * @param global Stores functions globally if true, locally otherwise.
        */
        template<typename T>void prepareType(const bool& global=false)
        {
            if (!global && static_cast<bool>(localTmpSpec) == true)
            {
                localTmpSpec->tmp_del.insert(std::make_pair(std::type_index(typeid(T)),def_del_func<T>));
                localTmpSpec->tmp_copy.insert(std::make_pair(std::type_index(typeid(T)),def_copy_func<T>));
            }
            else
            {
                globalTmpSpec.tmp_del.insert(std::make_pair(std::type_index(typeid(T)),def_del_func<T>));
                globalTmpSpec.tmp_copy.insert(std::make_pair(std::type_index(typeid(T)),def_copy_func<T>));
            }
        }

        /**
        * \brief Prepares cast function for given type.
        * @tparam B Base type.
        * @tparam T Type.
        * @param global Stores functions globally if true, locally otherwise.
        */
        template<typename B,typename T>void prepareCast(const bool& global=false)
        {
            if (!global && static_cast<bool>(localTmpSpec))
            {
                localTmpSpec->tmp_cast.insert(std::make_pair(std::make_pair(std::type_index(typeid(B)),std::type_index(typeid(T))),def_cast_func<B,T>));
            }
            else
            {
                globalTmpSpec.tmp_cast.insert(std::make_pair(std::make_pair(std::type_index(typeid(B)),std::type_index(typeid(T))),def_cast_func<B,T>));
            }
        }

        /**
        * \brief Returns stored value as \a T.
        * @tparam T Type.
        * @return Returns copy of stored objects if types matches, value of stored object casted to \a T or default \a T object otherwise.
        */
        template<typename T>operator T() const
        {
            if (_guard == typeid(T))
            {
                return *reinterpret_cast<T*>(_storage);
            }
            std::function<void*(void* &,Mtype&,const bool&)>func=getCastFunc(_guard,typeid(T));
            if (static_cast<bool>(func) == true)
            {
                return *reinterpret_cast<T*>(func(const_cast<void* &>(_storage),const_cast<Mtype&>(*this),false));
            }
            else
                return T();
        }

        /**
        * \brief Gets value of object as \a T& or \a T if possible.
        * @tparam T Type.
        * @param cast Prevents cast if set to true.
        * @return Returns reference to stored object if \a T matches object type, values of stored object casted to \a T (when cast == true and cast is available) or default \a T object otherwise.
        */
        template<typename T>dynamic_ref<T> get(const bool& cast=true) const
        {
            if (_guard==typeid(T))
            {
                return dynamic_ref<T>(const_cast<const T&>(*reinterpret_cast<T*>(_storage) ));
            }
            std::function<void*(void* &,Mtype&,const bool&)>func=getCastFunc(_guard,typeid(T));
            if (static_cast<bool>(func) == true && cast == true)
            {
                return dynamic_ref<T>(reinterpret_cast<T*>(func(const_cast<void* &>(_storage),const_cast<Mtype&>(*this),false)));
            }
            return dynamic_ref<T>();
        }

        /**
        * Gets stored object as \a T&.
        * \warning Potentially dangerous!<br>Note that is type of stored object and \a T does not match or \a T is void function throws invalid type exception.
        * @tparam T Type.
        * @return Returns direct reference to stored object.
        */
        template<typename T>UNSAFE T& forcedGet() const
        {
            if (_guard != typeid(T) && _guard == __voidId)
            {
                throw mt_exception_any("invalid type");
            }
            return *reinterpret_cast<T*>(_storage);
        }

        /**
        * \brief Sets current object value.
        * @tparam T new type of stored object.
        * @param target New value of stored object.
        * @return Returns true whenever type has changed by calling this function.
        */
        template<typename T>bool set(const T& target=T())
        {
            if (_guard==typeid(T))
            {
                *reinterpret_cast<T*>(_storage)=target;
                return false;
            }
            if (_storage!=nullptr)
            {
                std::function<void(void* const&)>func=getDelFunc(_guard);
                if (static_cast<bool>(func))
                {
                    func(_storage);
                }
                else
                {
                    throw mt_missing_delete();
                }
            }
            prepareType<T>();
            if (sizeof(T) > _size)
            {
                delete[] _buffer;
                _size = sizeof(T);
                _buffer = new char[_size];
            }
            _storage=new(_buffer) T(target);
            _guard=typeid(T);
            return true;
        }

        /**
        * \brief Casts value of object from \a B to \a T.
        * \note If \a B doesn't match objects type, objects has not been initialized or \a T is void function will throw invalid type exception.<br>
            Another fact worth mentioning is that this function adds cast from \a B to \a T if has not been added by this time.
        * @tparam B Base type.
        * @tparam T Type.
        * @param recast Cast will be applied to stored object when set to true.
        * @return Returns reference to stored object if \a B == \a T or object casted to from \a B to \a T otherwise.
        */
        template<typename B,typename T>dynamic_ref<T>cast(const bool& recast=false)
        {
            if (_guard!= typeid(B) || _guard == __voidId || __voidId == typeid(T))
            {
                throw mt_exception_any("invalid type");
            }
            if (_guard == typeid(T))
            {
                return dynamic_ref<T>(*reinterpret_cast<T*>(_storage));
            }
            std::function<void*(void* &,Mtype&,const bool&)>func=getCastFunc(_guard,typeid(T));
            if (static_cast<bool>(func) == true)
            {
                return dynamic_ref<T>(func(_storage,*this,false));
            }
            else
            {
                prepareCast<B,T>();
                return dynamic_ref<T>(def_cast_func<B,T>(_storage,*this,recast));
            }
        }

        /**
        * \brief Casts value of object from stored type to \a T.
        * @tparam T Type.
        * @param recast Cast will be applied to stored object when set to true.
        * @return Returns reference to stored object if \a T matches object type, object casted to \a T (when cast is available) or default \a T object otherwise.
        */
        template<typename T>dynamic_ref<T> autoCast(const bool& recast=false)
        {
            if (_guard == typeid(T))
            {
                return dynamic_ref<T>(*reinterpret_cast<T*>(_storage));
            }
            std::function<void*(void* &,Mtype&,const bool&)>func=getCastFunc(_guard,typeid(T));
            if (static_cast<bool>(func) == true)
            {
                return dynamic_ref<T>(func(_storage,*this,recast));
            }
            return dynamic_ref<T>(new T());
        }

        /**
        * \brief Default constructor.
        */
        Mtype() :_guard(__voidId) , type(_guard)
        {
            _storage = nullptr;
            localTmpSpec = std::shared_ptr<TempSpecifiers>(new TempSpecifiers());
            _size=0;
            _buffer=nullptr;
        }

        /**
        * \brief Copy constructor.
        */
        Mtype(const Mtype & target) :_guard(target._guard) , type(_guard)
        {
            localTmpSpec = target.localTmpSpec;
            _size=target._size;
            if (_size>0)
            {

                _buffer=new char[_size];
                if (_guard == __voidId)
                {
                    _storage = nullptr;
                }
                else
                {
                    std::function<void*(void* const&)>func = getCopyFunc(_guard);
                    if (static_cast<bool>(func) == true)
                    {
                        _storage = func(target._storage);
                    }
                    else
                    {
                        _storage = nullptr;
                        _guard = __voidId;
                        throw mt_missing_copy();
                    }
                }
            }
            else
            {
                _buffer=nullptr;
                _storage=nullptr;
            }
        }

        /**
        * \brief Move constructor.
        */
        Mtype(Mtype && target) :_guard(std::move(target._guard)) , _buffer(std::move(target._buffer)) , _size(std::move(target._size)) , _storage(std::move(target._storage)) , type(_guard){}

        /**
        * \brief Constructor that reserves memory block of size \a buff_size for later use.
        */
        Mtype(size_t buff_size) :_guard(__voidId) , type(_guard)
        {
            _storage=nullptr;
            _size=buff_size;
            _buffer=new char[_size];
        }

        /**
        * \brief Constructor that reserves memory block for \a T and creates \a T object inside it.
        */
        template<typename T>Mtype(const T& target)
        {
            prepareType<T>();
            _size=sizeof(T);
            _buffer=new char[_size];
            _storage=new(_buffer) T(target);
            _guard=typeid(T);
        }

        /**
        * \brief Virtual destructor(cleans up memory).
        */
        virtual ~Mtype() throw(mt_exception)
        {
            if (_storage!=nullptr)
            {
                std::function<void(void* const&)>func=getDelFunc(_guard);
                if (static_cast<bool>(func) == true)
                {
                    func(_storage);
                }
                else
                {
                    throw mt_missing_delete();
                }
            }
            delete[] _buffer;
        }
    };
}
#endif // MTYPE_H_INCLUDED
