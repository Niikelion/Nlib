#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

#include"nlib/utility/err11.h"
#include<functional>

namespace Nlib
{
    /**
    * \class Initializer
    * \brief Executes function on creation and destruction.
    */
    class Initializer final
    {
        std::function<void()>_deinit;
    public:
        Initializer() = delete;
        Initializer(std::function<void()>init ,std::function<void()>deinit = std::function<void()>());
        Initializer(const Initializer & target) = delete;
        Initializer(Initializer&& target) noexcept;
        ~Initializer();
    };
}

#endif // INIT_H_INCLUDED
