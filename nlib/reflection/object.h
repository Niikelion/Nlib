#ifndef OBJECT_H
#define OBJECT_H

#include <map>
#include <algorithm>
#include <functional>

namespace Nlib
{
    class Object
    {
        static std::map<std::string,std::function<void*()>> types; //consider ctti lib
    public:
        //template<typename T>registerType
    };
}

#endif // OBJECT_H
