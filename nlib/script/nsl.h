#ifndef NSL_H_INCLUDED
#define NSL_H_INCLUDED


#include<string>
#include<vector>
#include<nlib/utility/mtype.h>

class RawToken
{
public:
    struct Types{enum TYPES{CHAR=0,SEP,QUOTE,RET,WORD};};
    unsigned int type,subtype;
    char data;
    RawToken();
    RawToken(char base);
    RawToken(const RawToken&target);
    ~RawToken();
};



class CmpToken
{
    //
};

class Interpreter
{
    std::vector<CmpToken>tokens;
public:
    void prepare(std::string source);
};

#endif // NSL_H_INCLUDED
