#ifndef MATHSCR_H
#define MATHSCR_H

#include <map>
#include <string>
#include <vector>
#include <utility>
#include <functional>
#include <initializer_list>

#include <nlib/utility/mtype.h>

namespace Nlib
{
    class MathScript
    {
    public:

    protected:

        class rawToken
        {
        public:
            virtual std::string getType()=0;
            virtual Mtype getValue()=0;

            virtual ~rawToken() = default;
        };

        class rawSepToken:public rawToken
        {
        public:
            unsigned int type;
            virtual std::string getType();
            virtual Mtype getValue();

            rawSepToken()noexcept = default;
            rawSepToken(const rawSepToken&)noexcept = default;
            rawSepToken(rawSepToken&&)noexcept = default;

            rawSepToken(const char&);

            virtual ~rawSepToken();
        };

        class rawCharToken:public rawToken
        {
        public:
            char value;
            virtual std::string getType();
            virtual Mtype getValue();

            rawCharToken()noexcept = default;
            rawCharToken(const rawCharToken&)noexcept = default;
            rawCharToken(rawCharToken&&)noexcept = default;

            rawCharToken(const char&)noexcept;

            virtual ~rawCharToken();
        };

        class rawStringToken:public rawToken
        {
        public:
            std::string value;
            virtual std::string getType();
            virtual Mtype getValue();

            rawStringToken() = default;
            rawStringToken(const rawStringToken&) = default;
            rawStringToken(rawStringToken&&)noexcept = default;

            rawStringToken(const std::string&);

            virtual ~rawStringToken();
        };

        class rawValueToken:public rawToken
        {
        public:
            virtual std::string getType()=0;
            virtual Mtype getValue()=0;

            virtual ~rawValueToken() = default;
        };

        class rawIntegerToken:public rawValueToken
        {
        public:
            unsigned int value;
            virtual std::string getType();
            virtual Mtype getValue();

            virtual ~rawIntegerToken();
        };

        class rawFloatToken:public rawValueToken
        {
        public:
            double value;
            virtual std::string getType();
            virtual Mtype getValue();

            virtual ~rawFloatToken();
        };

        class rawStringValToken:public rawValueToken
        {
        public:
            std::string value;
            virtual std::string getType();
            virtual Mtype getValue();

            virtual ~rawStringValToken();
        };

    public:
        class Token
        {
        public:
            virtual std::string getType()=0;
            virtual Mtype getValue()=0;

            virtual ~Token() = default;
        };
        class valueToken:public Token
        {
        public:
            Mtype value;
            virtual std::string getType();
            virtual Mtype getValue();

            virtual ~valueToken() throw();
        };

        class funcToken: public Token
        {
        public:
            std::function<valueToken(std::initializer_list<valueToken>)>func;

            virtual std::string getType();
            virtual Mtype getValue();

            virtual ~funcToken();
        };

        std::map<std::string,funcToken> functions,operators;

        bool tokenize(const std::string& source);

    };
}
#endif // MATHSCR_H
