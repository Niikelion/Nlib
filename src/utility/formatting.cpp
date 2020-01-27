#include "nlib/utility/formatting.h"

namespace Nlib
{
    std::string format(const std::string& source,const std::string& flags,const int& pos,const bool& extend,const int& pos1)
    {
        int _pos=pos;
        bool raw=false;
        switch (flags.size()-1)
        {
        case 0:
            {
                std::string line;
                bool start=(_pos==0);
                for (unsigned int i=0; i<source.size(); i++)
                {
                    if (source[i]=='"')
                    {
                        raw=!raw;
                    }
                    else if (source[i]==flags[0] and !raw)
                    {
                        _pos--;
                        if (_pos<0 and !extend) break;
                    }
                    if (_pos==0 or (_pos<=0 and extend))
                    {
                        if (start)
                            line+=source[i];
                        start=true;
                    }
                }
                return line;
            }
        case 1:
            {
                std::string line;
                unsigned int brackets=0;
                bool start=false;
                for (unsigned int i=0; i<source.size(); i++)
                {
                    if (source[i]=='"')
                    {
                        raw=!raw;
                    }
                    if (source[i]==flags[0] and !raw)
                    {
                        brackets++;
                        if (pos==0)
                        {
                            if (start) line+=source[i];
                            start=true;
                        }
                    }
                    else if (source[i]==flags[1] and !raw)
                    {
                        brackets--;
                        if (brackets==0)
                        {
                            _pos--;
                            if (pos<0 and !extend)
                                break;
                        }
                        if (brackets>0 and _pos==0)
                            line+=source[i];
                    }
                    else if (start)
                    {
                        line+=source[i];
                    }
                }
                return line;
            }
        case 2:
            {
                return format(format(source,std::string()+flags[0]+flags[2],pos1),std::string()+flags[1],pos);
            }
        }
        return std::string();
    }
    std::string random_string(unsigned int len)
    {
        static bool randed=false;
        if (!randed)
        {
            srand(time(NULL));
            randed=true;
        }
        //std::mt19937 rng;
        //rng.seed(std::random_device()());
        //std::uniform_int_distribution<std::mt19937::result_type> distdev('A','Z');

        std::string help="";
        for (unsigned int i=0; i<len; ++i)
        {
            help+=char('A'+(rand()%('Z'-'A')));
        }
        return help;
    }
}
