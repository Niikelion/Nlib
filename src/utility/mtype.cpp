#include "nlib/utility/mtype.h"

namespace Nlib
{
    Mtype::TempSpecifiers::TempSpecifiers(TempSpecifiers&& target) noexcept:tmp_del(std::move(target.tmp_del)),tmp_copy(std::move(target.tmp_copy)),tmp_cast(std::move(target.tmp_cast))
    {/**/}

    std::type_index Mtype::__voidId = typeid(void);
    Mtype::TempSpecifiers Mtype::globalTmpSpec;
}
