#ifndef N_REFERENCE_H_INCLUDED
#define N_REFERENCE_H_INCLUDED

#include<nlib/utility/err11.h>
#include<utility>

namespace Nlib
{
    /**
    * \class dynamic_ref
    * \brief Dynamic reference wrapper
    *
    * Stores reference to object, object or nothing.<br>
    * It creates new object if you try to access stored object when there is nothing.
    */
    template<typename T>class dynamic_ref
    {
    protected:
        T* _storage;
        bool _isowner;
    public:
        const bool& isOwner;/**< Is set to true when dynamic_ref is owner of stored object. */

        /**
        * \brief Sets value of stored object to \a target.
        * @param target Value to be set.
        * @return Reference to this.
        */
        dynamic_ref<T>& operator = (const T& target)
        {
            if (_storage == nullptr)
            {
                _storage = new T();
                _isowner = true;
            }
            *_storage = target;
            return *this;
        }

        /**
        * \brief Returns reference to stored object.
        * Returns reference to stored object. If there if no stored object it creates new one.
        */
        explicit operator T&()
        {
            if (_storage == nullptr)
            {
                _storage = new T();
                _isowner = true;
            }
            return *_storage;
        }

        /**
        * \brief Returns copy of stored object.
        * Returns copy of stored object if exists, default T object otherwise.
        */
        operator T() const noexcept
        {
            if (_storage == nullptr)
                return std::move(T());
            return *_storage;
        }

        /**
        * \brief Returns pointer to stored object.
        * Returns pointer to stored object if exists, nullptr otherwise.
        */
        explicit operator T*() const noexcept
        {
            return _storage;
        }

        /**
        * \brief Stores reference to \a source.
        */
        explicit dynamic_ref<T>(const T& source) noexcept :isOwner(_isowner)
        {
            _storage=const_cast<T*>(&source);
            _isowner=false;
        }

        /**
        * \brief Stores \a source value.
        */
        explicit dynamic_ref<T>(T* source) :isOwner(_isowner)
        {
            _storage=new T(*source);
            _isowner=true;
        }

        dynamic_ref<T>() noexcept :isOwner(_isowner)
        {
            _storage=nullptr;
            _isowner=false;
        }
        dynamic_ref<T>(const dynamic_ref<T>& target) :isOwner(_isowner)
        {
            _isowner = target._isowner;
            if (_isowner && target._storage != nullptr)
            {
                _storage = new T(*target._storage);
            }
            else
            {
                _storage = nullptr;
            }
        }
        dynamic_ref<T>(dynamic_ref<T>&& target)noexcept :_storage(std::move(target._storage)) , _isowner(std::move(target._isowner)) , isOwner(_isowner){}

        virtual ~dynamic_ref<T>()
        {
            if (_isowner)
            {
                delete _storage;
            }
        }
    };
}

#endif // n_reference
