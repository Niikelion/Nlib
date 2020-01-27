#include "nlib\script\nsl.h"

RawToken::RawToken()
{
    type=0;
    subtype=0;
    data=0;
}
RawToken::RawToken(char base)
{
    type=Types::CHAR;
    data=base;
    subtype=0;
    switch (base)
    {
    case ' ':
        {
            type=Types::SEP;
            break;
        }
    case "'"[0]:
        {
            type=Types::QUOTE;
            subtype=0;
            break;
        }
    case '"':
        {
            type=Types::QUOTE;
            subtype=1;
            break;
        }
    case ';':
        {
            type=Types::RET;
            break;
        }
    default:
        {/**/}
    }
}

void Interpreter::prepare(std::string source)
{
    std::vector<RawToken>rawtokens;
    for (size_t i=0; i<source.size(); ++i)
    {
        rawtokens.push_back(RawToken(source[i]));
    }

}
