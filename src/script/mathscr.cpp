#include "nlib\script\mathscr.h"

namespace Nlib
{
    std::string MathScript::rawSepToken::getType()
    {
        return std::move("rawSep");
    }

    Mtype MathScript::rawSepToken::getValue()
    {
        Mtype tmp;
        tmp.set(type);
        return std::move(tmp);
    }



    MathScript::rawCharToken::rawCharToken(const char& a) noexcept
    {
        value=a;
    }

    std::string MathScript::rawCharToken::getType()
    {
        return std::move("rawChar");
    }

    Mtype MathScript::rawCharToken::getValue()
    {
        Mtype temp;
        temp.set(value);
        return std::move(temp);
    }

    MathScript::rawStringToken::rawStringToken(const std::string& a)
    {
        value=a;
    }

    std::string MathScript::rawStringToken::getType()
    {
        return std::move("rawString");
    }
    Mtype MathScript::rawStringToken::getValue()
    {
        Mtype temp;
        temp.set(value);
        return std::move(temp);
    }

    std::string MathScript::rawIntegerToken::getType()
    {
        return std::move("rawInteger");
    }
    Mtype MathScript::rawIntegerToken::getValue()
    {
        Mtype temp;
        temp.set(value);
        return std::move(temp);
    }

    std::string MathScript::rawFloatToken::getType()
    {
        return std::move("rawFloat");
    }
    Mtype MathScript::rawFloatToken::getValue()
    {
        Mtype temp;
        temp.set(value);
        return std::move(temp);
    }

    std::string MathScript::rawStringValToken::getType()
    {
        return std::move(value);
    }
    Mtype MathScript::rawStringValToken::getValue()
    {
        Mtype temp;
        temp.set(value);
        return std::move(temp);
    }

    bool MathScript::tokenize(const std::string& source)
    {
        std::vector<std::reference_wrapper<rawToken> >rawTokens;
        rawTokens.reserve(source.size());
        int quo=-1;
        std::string curr;
        for (unsigned int i=0; i<source.size(); ++i)
        {
            if (source[i]=='"')
            {
                if (quo==-1)
                {
                    quo=i;
                    curr.clear();
                }
                else
                {
                    quo=-1;
                    rawTokens.push_back(std::ref(*reinterpret_cast<rawToken*>(new rawStringToken(curr))));
                }
            }
            else
            {
                if (quo!=-1 && source[i]=='\\' && i!=source.size()-1 && source[i+1]=='"')
                {
                    ++i;
                    curr+='"';
                }
                else if (quo!=-1)
                {
                    if (source[i]==13)
                        continue;
                   curr+=source[i];
                }
                else
                {
                    if (source[i]==' ' || source[i]==';')
                        rawTokens.push_back(std::ref(*reinterpret_cast<rawToken*>(new rawSepToken(source[i]))));
                    else
                        rawTokens.push_back(std::ref(*reinterpret_cast<rawToken*>(new rawCharToken(source[i]))));
                }
            }
        }

        std::vector<std::reference_wrapper<Token> >tokens;

        for (int i=0; i<tokens.size(); ++i)
        {
            //
        }

        ///group tokens into more complex tokens
    }
}
