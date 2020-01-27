#include "types.h"

namespace Nlib
{
    namespace Debug
    {
        template<> var_cast<int>(const Value::shared& v)
        {
            if (v)
            {
                std::type_index t = v->type();
                if (t == typeid(int))
                {
                    return _get_value<int>(v);
                }
                else if (t == typeid(std::string))
                {
                    return std::stoi(_get_value<std::string>(v));
                }
                else if (t == typeid(unsigned))
                {
                    return _get_value<unsigned>(v);
                }
                else if (t == typeid(long long))
                {
                    return _get_value<long long>(v);
                }
                else if (t == typeid(unsigned long long))
                {
                    return _get_value<unsigned long long>(v);
                }
                else if (t == typeid(float))
                {
                    return _get_value<float>(v);
                }
                else if (t == typeid(double))
                {
                    return _get_value<double>(v);
                }
            }
            return 0;
        }
    }
}
