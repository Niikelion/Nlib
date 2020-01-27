#ifndef ERRORS_H_INCLUDED
#define ERRORS_H_INCLUDED
#include<string>
#include<vector>
#include<nlib/utility/convert.h>
#define push_error(source,code) Nlib::error_queue.push_front(Nlib::error(__FILE__,__LINE__,source,code));

namespace Nlib
{
    class NERRORS
    {
    public:

        enum ERRORS{
            NONE=0,
            MEMORY_LEAK
        };
    };
    class error
    {
    public:

        unsigned int type,line,lvl;
        std::string file,source;
        std::string toString();
        error();
        error(std::string,unsigned int,std::string,unsigned int,unsigned int=0);
        error(const error&)=default;
    };
    std::vector<error>error_queue;
    std::vector<std::string>error_lvl;
}



#endif // ERRORS_H_INCLUDED
