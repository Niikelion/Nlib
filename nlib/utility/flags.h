#ifndef N_FLAGS_H_INCLUDED
#define N_FLAGS_H_INCLUDED

#include <cstdint>
#include <utility>

namespace Nlib
{
    /**
    * \class FMask
    * \brief Manages masks and flags.
    * Class designed to store flags. Has functions to add, remove and toggle flags specified by mask.
    */
    class FMask
    {
    public:

        uint32_t flags;/**< \brief Stored masks. */
        /**
        * \brief Checks if specified mask i set.
        * @param mask Mask.
        * @return Returns true if mask is set.
        */
        bool isSet(const uint32_t& mask) const noexcept;
        /**
        * \brief Sets specified mask.
        * @param mask Mask.
        */
        void set(const uint32_t& mask) noexcept;
        /**
        * \brief Removes specified mask.
        * @param mask Mask.
        */
        void remove(const uint32_t& mask) noexcept;
        /**
        * \brief Toggles specified mask.
        * @param mask Mask.
        */
        void toggle(const uint32_t& mask) noexcept;
        /**
        * \brief Clears all masks.
        */
        void clear() noexcept;
///----------------------------------------------
        bool operator == (const FMask& target) const noexcept;
        bool operator == (const uint32_t& mask) const noexcept;

        FMask  operator |  (const FMask& target) const noexcept;
        FMask  operator |  (const uint32_t& target) const noexcept;
        FMask& operator |= (const FMask& target) noexcept;
        FMask& operator |= (const uint32_t& target) noexcept;

        FMask  operator &  (const FMask& target) const noexcept;
        FMask  operator &  (const uint32_t& target) const noexcept;
        FMask& operator &= (const FMask& target) noexcept;
        FMask& operator &= (const uint32_t& target) noexcept;

        /**
        * \brief Removes specified mask.
        * @param target Mask.
        * @return Result of operation.
        */
        FMask  operator -  (const FMask& target) const noexcept;
        /**
        * @copydoc FMask::operator-()
        */
        FMask  operator -  (const uint32_t& target) const noexcept;
        /**
        * \brief Removes specified mask.
        * @param target Mask.
        * @return Reference to itself.
        */
        FMask& operator -= (const FMask& target) noexcept;
        /**
        * @copydoc FMask::operator-=()
        */
        FMask& operator -= (const uint32_t& target) noexcept;

        FMask operator ~ () const noexcept;

        FMask  operator ^  (const FMask& target) const noexcept;
        FMask  operator ^  (const uint32_t& target) const noexcept;
        FMask& operator ^= (const FMask& target) noexcept;
        FMask& operator ^= (const uint32_t& target) noexcept;

        FMask & operator = (FMask && target) noexcept = default;
        FMask & operator = (const FMask& target) noexcept = default;
        FMask & operator = (const uint32_t& FMask) noexcept;

        operator uint32_t() const noexcept;

        FMask operator ! () const noexcept;
///----------------------------------------------
        FMask() noexcept;
        FMask(const uint32_t& mask) noexcept;
        FMask(FMask && target) noexcept = default;
        FMask(const FMask & target) noexcept = default;

         virtual ~FMask() noexcept = default;
    };
}

#endif // n_flags
