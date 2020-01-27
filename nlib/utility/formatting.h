#ifndef FORMATTING_H
#define FORMATTING_H

#include <string>
#include <ctime>
#include <random>

namespace Nlib
{
    /**
    * \brief Formats string.
    * Splits string by separator, extracts string between enclosing characters or does both.<br><br>
      If size of \a flags == 1 function will use flags[0] as a separator to split \a source .<br>
      If size of \a flags == 2 function will use flags[0] && flags[1] as enclosing characters to extract string.<br>
      If size of \a flags == 3 function will use flags[0] && flags[2] as enclosing characters && flags[1] as separator to extract string.
    * @param[in] source Source string.
    * @param[in] flags Flags to format the string.
    * @param[in] pos Index of string to extract.
    * @param[in] extend When set to true, will split string to max 2 parts.
    * @param[in] pos1 If size of \a flags == 3 it determines the split string index.
    * @return Returns formatted string.
    */
    std::string format(const std::string& source,const std::string& flags,const int& pos = 0,const bool& extend = false,const int& pos1=0);
    std::string random_string(unsigned int len);
}
#endif // FORMATTING_H
