#include<nlib/utility/flags.h>

namespace Nlib
{
    bool FMask::isSet(const uint32_t& mask) const noexcept
    {
        return std::move(flags & mask);
    }
    void FMask::set(const uint32_t& mask) noexcept
    {
        flags |= mask;
    }
    void FMask::remove(const uint32_t& mask) noexcept
    {
        flags &= ~mask;
    }
    void FMask::toggle(const uint32_t& mask) noexcept
    {
        flags ^= mask;
    }
    void FMask::clear() noexcept
    {
        flags = 0;
    }
///----------------------------------------------
    bool FMask::operator == (const FMask& target) const noexcept
    {
        return std::move(flags == target.flags);
    }
    bool FMask::operator == (const uint32_t& mask) const noexcept
    {
        return std::move(flags == mask);
    }

    FMask FMask::operator | (const FMask& target) const noexcept
    {
        return std::move(FMask(flags | target.flags));
    }
    FMask FMask::operator | (const uint32_t& target) const noexcept
    {
        return std::move(FMask(flags | target));
    }
    FMask& FMask::operator |= (const FMask& target) noexcept
    {
        flags |= target.flags;
        return *this;
    }
    FMask& FMask::operator |= (const uint32_t& target) noexcept
    {
        flags |= target;
        return *this;
    }


    FMask FMask::operator& (const FMask& target) const noexcept
    {
        return std::move(FMask(flags & target.flags));
    }
    FMask FMask::operator& (const uint32_t& target) const noexcept
    {
        return std::move(FMask(flags & target));
    }
    FMask& FMask::operator&= (const FMask& target) noexcept
    {
        flags &= target.flags;
        return *this;
    }
    FMask& FMask::operator&= (const uint32_t& target) noexcept
    {
        flags &= target;
        return *this;
    }

    FMask FMask::operator - (const FMask& target) const noexcept
    {
        return std::move(FMask(flags & (~target.flags) ));
    }
    FMask FMask::operator - (const uint32_t& target) const noexcept
    {
        return std::move(FMask(flags & (~target) ));
    }
    FMask& FMask::operator -= (const FMask& target) noexcept
    {
        flags &= ~target.flags;
        return *this;
    }
    FMask& FMask::operator -= (const uint32_t& target) noexcept
    {
        flags &= ~target;
        return *this;
    }

    FMask FMask::operator ~ () const noexcept
    {
        return std::move(FMask(~flags));
    }

    FMask FMask::operator ^ (const FMask& target) const noexcept
    {
        return std::move(FMask(flags ^ target.flags));
    }
    FMask FMask::operator ^ (const uint32_t& target) const noexcept
    {
        return std::move(FMask(flags ^ target));
    }
    FMask& FMask::operator ^= (const FMask& target) noexcept
    {
        flags ^= target.flags;
        return *this;
    }
    FMask& FMask::operator ^= (const uint32_t& target) noexcept
    {
        flags ^= target;
        return *this;
    }

    FMask & FMask::operator = (const uint32_t& mask) noexcept
    {
        flags = mask;
        return *this;
    }

    FMask::operator uint32_t() const noexcept
    {
        return flags;
    }

    FMask FMask::operator ! () const noexcept
    {
        return std::move(FMask(~flags));
    }
///----------------------------------------------
    FMask::FMask() noexcept
    {
        flags=0;
    }
    FMask::FMask(const uint32_t& mask) noexcept
    {
        flags=mask;
    }
}
