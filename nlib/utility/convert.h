#ifndef CONVERT_H_INCLUDED
#define CONVERT_H_INCLUDED

#include<string>
#include<cinttypes>
#include<limits>
#include<algorithm>

namespace Nlib
{
    template<typename T>struct effsize{static constexpr size_t value = 0;};
    template<>struct effsize<double>{static constexpr size_t value = 12;};
    template<>struct effsize<float>{static constexpr size_t value = 6;};

    /**
    * \brief Converts number to string.
    * @param num Number to be converted.
    * @param places Digits after comma to be displayed.
    * @return Number converted to string.
    */
    template<typename T>std::string to_string(T num,uint32_t places = effsize<T>::value)
    {
        std::string ret;
        bool dir = false;
        if (num < 0)
        {
            num *= -1;
            dir = true;
        }

        uint32_t base = static_cast<uint32_t>(num);
        T _rest = num - base;
        while (places > 0)
        {
            _rest *= 10;
            places--;
        }
        uint64_t rest = static_cast<uint64_t>(_rest);
        if (rest != 0)
        {
            while (rest > 0)
            {
                ret += '0' + (rest % 10);
                rest /= 10;
            }
            ret += '.';
        }
        if (base == 0)
            ret += '0';
        while (base > 0)
        {
            ret += '0' + (base % 10);
            base /= 10;
        }
        if (dir)
            ret += '-';
        for (size_t i = 0; i < ret.size() / 2; ++i)
            std::swap(ret[i],ret[ret.size()-1-i]);
        return std::move(ret);
    }

    /**
    * \brief Check if given string is an integer.
    * @param source Given string.
    * @return true if \a source is proper integer and can be converted to int without error.
    */
    bool is_integer(const std::string& source);

}

#endif // CONVERT_H_INCLUDED
