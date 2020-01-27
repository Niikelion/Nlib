#include "nlib/utility/convert.h"

namespace Nlib
{
    bool is_integer(const std::string& s)
    {
        std::string buff(s);
        if (buff.find('-')==0)
            buff.erase(buff.begin());
        return std::move((!buff.empty() && std::find_if(buff.begin(),
            buff.end(), [](char c) { return !std::isdigit(c); }) == buff.end()));
    }
}
