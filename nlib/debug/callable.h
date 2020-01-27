#ifndef CALLABLE_H
#define CALLABLE_H

#include <nlib/debug/types.h>
#include <functional>
#include <iostream>
#include <cmath>

namespace Nlib
{
    namespace Debug
    {
        class Callable
        {
        public:
            typedef std::shared_ptr<Callable> shared;
            virtual Value::shared operator() (const std::vector<Value::shared>&)const=0;
        };

        /**----------------------------------------------------------------**/

        template<typename T,typename std::enable_if<!std::is_reference<T>::value>::type* = nullptr> T _unpack_param(const std::vector<Value::shared>& a,unsigned& i)
        {
            --i;
            return (i<a.size())?var_cast<T>(a[i]):T();
        }
        template<typename T,typename std::enable_if<std::is_reference<T>::value>::type* = nullptr> T _unpack_param(const std::vector<Value::shared>& a,unsigned& i)
        {
            --i;

            if (i<a.size())
                return var_cast<T>(a[i]);
            throw std::logic_error("run out of arguments");
        }

        template<typename T,typename... ArgT>class CallableFunction: public Callable
        {
        protected:
            std::function<T(ArgT...)> f;
        public:
            Value::shared operator() (const std::vector<Value::shared>& v)const
            {
                unsigned i = sizeof...(ArgT);
                return var(f(_unpack_param<ArgT>(v,i)...));
            }
            CallableFunction(std::function<T(ArgT...)> _f)
            {
                f = _f;
            }
        };

        /**----------------------------------------------------------------**/

        class Function
        {
        private:
            Callable::shared binding;
        public:
            Value::shared operator() (const std::vector<Value::shared>&)const;
            Function& operator = (const Callable::shared&);

            Function(const Callable::shared&);
        };

        template<typename T,typename... ArgT>Callable::shared fun(T(*f)(ArgT...))
        {
            return std::make_shared<CallableFunction<T,ArgT...>>(f);
        }
        template<typename T,typename... ArgT>Callable::shared lambda(std::function<T(ArgT...)> f)
        {
            return std::make_shared<CallableFunction<T,ArgT...>>(f);
        }
    }
}

#endif // CALLABLE_H
