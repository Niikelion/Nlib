#include "nlib/utility/init.h"
namespace Nlib
{
    Initializer::Initializer(std::function<void()>init,std::function<void()>deinit):_deinit(deinit)
    {
        init();
    }
    Initializer::Initializer(Initializer&& target)noexcept: _deinit(std::move(target._deinit))
    {
        target._deinit = nullptr;
    }
    Initializer::~Initializer()
    {
        _deinit();
    }
}
