#include "callable.h"

namespace Nlib
{
    namespace Debug
    {
        Value::shared Function::operator() (const std::vector<Value::shared>& v)const
        {
            return (binding)?binding->operator()(v):Value::shared();
        }
        Function& Function::operator = (const Callable::shared& a)
        {
            binding = a;
            return *this;
        }

        Function::Function(const Callable::shared& a)
        {
            binding = a;
        }
    }
}
