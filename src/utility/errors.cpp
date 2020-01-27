#include <nlib/utility/errors.h>

namespace Nlib
{
    std::string error::toString()
    {
        std::string val;///\todo setup
        if (lvl!=0)
        {
            val=Nlib::to_string<unsigned int>(type);
        }
        else
        {
            switch (type)
            {
            case NERRORS::NONE:
                {
                    val="none";
                    break;
                }
            case NERRORS::MEMORY_LEAK:
                {
                    val="memory leak";
                    break;
                }
            }
        }
        std::string tmp=file+" at line "+Nlib::to_string<unsigned int>(line)+": "+source+"("+val+") form"+(lvl==0?"Nlib":error_lvl[lvl-1]);
        return tmp;
    }
    error::error()
    {
        line=0;
        type=0;
        lvl=0;
    }
    error::error(std::string _file,unsigned int _line,std::string _target,unsigned int _error,unsigned int _lvl)
    {
        file=_file;
        line=_line;
        source=_target;
        type=_error;
        lvl=_lvl;
    }
}

