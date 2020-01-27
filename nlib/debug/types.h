#ifndef TYPES_H
#define TYPES_H

#include <memory>
#include <string>
#include <vector>
#include <typeindex>
#include <cstdlib>
#include <iostream>

namespace Nlib
{
    namespace Debug
    {
        class Value
        {
        public:
            typedef std::shared_ptr<Value> shared;

            virtual std::type_index type() const noexcept=0;
            virtual std::string toString() const=0;
        };

        template<typename T>class Value_t: public Value
        {
        public:
            T value;
            std::type_index type() const noexcept
            {
                return typeid(T);
            }

            std::string toString() const
            {
                return std::string("value of type ")+type().name();
            }
            Value_t()=default;
            Value_t(const Value_t<T>&t)=default;
            Value_t(Value_t<T>&&t)noexcept=default;

            Value_t(const T& v):value(v){}
        };

        template<>class Value_t<int>: public Value
        {
        public:
            int value;
            std::type_index type() const noexcept
            {
                return typeid(int);
            }

            std::string toString() const
            {
                return std::to_string(value);
            }
            Value_t()
            {
                value = 0;
            }
            Value_t(const Value_t<int>&)=default;
            Value_t(Value_t<int>&&)noexcept = default;

            Value_t(int v)
            {
                value = v;
            }
        };

        template<>class Value_t<std::string>: public Value
        {
        public:
            std::string value;
            std::type_index type() const noexcept
            {
                return typeid(std::string);
            }

            std::string toString() const
            {
                return value;
            }
            Value_t() = default;
            Value_t(const Value_t<std::string>&)=default;
            Value_t(Value_t<std::string>&&)noexcept = default;

            Value_t(std::string v)
            {
                value = v;
            }
        };

        template<>class Value_t<bool>: public Value
        {
        public:
            bool value;
            std::type_index type() const noexcept
            {
                return typeid(bool);
            }

            std::string toString() const
            {
                return std::to_string(value);
            }
            Value_t()
            {
                value = 0;
            }
            Value_t(const Value_t<bool>&)=default;
            Value_t(Value_t<bool>&&)noexcept = default;

            Value_t(bool v)
            {
                value = v;
            }
        };

        template<typename T>Value::shared var(const T& v)
        {
            return std::make_shared<Value_t<T> >(v);
        }

        template<typename T,typename std::enable_if<!std::is_reference<T>::value>::type* = nullptr>T _get_value(const Value::shared& v)
        {
            return static_cast<Value_t<T>*>(v.get())->value;
        }

        template<typename T,typename std::enable_if<std::is_reference<T>::value>::type* = nullptr>T _get_value(const Value::shared& v)
        {
            return static_cast<Value_t<std::reference_wrapper<typename std::remove_reference<T>::type>>*>(v.get())->value;
        }

        template<typename T>struct _val_con
        {
            T operator() (const std::string&)
            {
                return T();
            }
        };

        template<>struct _val_con<int>
        {
            int operator() (const std::string& val)
            {
                return std::strtol(val.c_str(),nullptr,10);
            }
        };

        template<>struct _val_con<std::string>
        {
            std::string operator() (const std::string& val)
            {
                return val;
            }
        };

        template<>struct _val_con<bool>
        {
            bool operator() (const std::string& val)
            {
                if (val == "0" || val == "false" || val.size() == 0)
                    return false;
                return true;
            }
        };

        template<typename T,typename std::enable_if<!std::is_reference<T>::value>::type* = nullptr>T var_cast(const Value::shared& v)
        {
            if (v && v->type() == typeid(T))
            {
                return _get_value<T>(v);
            }
            return _val_con<T>()(v->toString());
        }

        template<typename T,typename std::enable_if<std::is_reference<T>::value>::type* = nullptr>T var_cast(const Value::shared& v)
        {
            if (v && v->type() == typeid(std::reference_wrapper<typename std::remove_reference<T>::type>))
            {
                return _get_value<T>(v);
            }
            throw std::logic_error("mismatched types");
        }
        struct _db
        {
            bool b[2];
        };
        template<typename T,typename Arg>_db operator >> (const Arg&,const T&);
        bool _sub_check(...);
        _db _sub_check(const _db&);
        template<typename T,typename Arg = std::istream> struct _has_stream_operator
        {
            enum {value = (sizeof(_sub_check(*(Arg*)(0)>>*(T*)(0))) != sizeof(_db))};
        };

        template<typename T,typename std::enable_if<_has_stream_operator<T>::value>::type* = nullptr>Value::shared var_load(std::istream& a=std::cin)
        {
            std::shared_ptr<Value_t<T>> ret = std::make_shared<Value_t<T>>();
            a >> ret -> value;
            return ret;
        }
        template<typename T,typename = decltype(var_cast<T>),typename std::enable_if<!_has_stream_operator<T>::value>::type* = nullptr> Value::shared var_load(std::istream& a=std::cin)
        {
            std::string b;
            a >> b;
            return std::make_shared<Value_t<T>>(var_cast<T>(std::make_shared<Value_t<std::string>>()));
        }
    }
}

#endif // TYPES_H
