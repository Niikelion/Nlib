#ifndef LINT_H_INCLUDED
#define LINT_H_INCLUDED

#include <cstring>
#include <string>
#include <cinttypes>
#include <utility>
#include <algorithm>
#include <limits>
#include <cmath>

namespace Nlib
{
    /**
    * @class LintStorage
    * @brief Manages memory for LintS.
    */
    class LintStorage
    {
        union
        {
            uint64_t _size;
            struct
            {
                uint32_t _msize;
                uint32_t _tsize;
            };
        };
        uint64_t * _storage;
    public:
        uint64_t & operator [] (const size_t& index) const noexcept;
        size_t size() const noexcept;
        size_t size(const size_t& index);

        LintStorage & operator = (const LintStorage & target);
        LintStorage & operator = (LintStorage&& target);

        LintStorage() noexcept;
        LintStorage(const size_t& index);
        LintStorage(LintStorage && target) noexcept;
        LintStorage(const LintStorage & target);
        virtual ~LintStorage();
    };

    /**
    * @class LintS
    * @brief Basic class for storing big unsigned integers.
    * LintS is designed to store huge unsigned integers that are far larger than 64 bit.
    It also provides basic arithmetic functions and conversion to string.
    */
    class LintS
    {
    protected:
        static constexpr uint64_t max10pow()
        {
            return static_cast<uint64_t>(floor(pow(10,floor(log10(~0ULL)))));
            //return 1;
        }

        static constexpr uint64_t max10digits()
        {
            return static_cast<uint64_t>(floor(log10(~0ULL)));
            //return 1000000000000000000; // max power of 10 in uint64
        }

        static uint32_t lost(const uint64_t num);
        static uint32_t hist(const uint64_t num);

    public:
        LintStorage _storage;
    protected:
        constexpr static uint64_t nu = ~0ULL;
        constexpr static uint64_t last_b = (nu^(nu<<1));
        constexpr static size_t true_size = sizeof(uint64_t)*8;
    public:
        /**
        * @brief Size of storage passed via constructor.
        * Size of storage.
        * @note Please note that storage can be in fact slightly larger because it is a multiple of 8.
        */
        const uint32_t size;

        LintS & operator =   (const uint64_t & target) noexcept;
        LintS & operator =   (const LintS& target) noexcept;

        bool    operator ==  (const LintS& target) const noexcept;
        bool    operator <   (const LintS& target) const noexcept;
        bool    operator <=  (const LintS& target) const noexcept;
        bool    operator >   (const LintS& target) const noexcept;
        bool    operator >=  (const LintS& target) const noexcept;

        LintS & operator <<= (const size_t& index) noexcept;
        LintS & operator >>= (const size_t& index) noexcept;

        LintS & operator +=  (const LintS& target) noexcept;
        LintS & operator -=  (const LintS& target) noexcept;
        LintS & operator *=  (const LintS& target) noexcept;
        LintS & operator /=  (const LintS& target) noexcept;
        LintS & operator %=  (const LintS& target) noexcept;

        LintS   operator <<  (const size_t& index) const noexcept;
        LintS   operator >>  (const size_t& index) const noexcept;



        LintS   operator +   (const LintS& target) const noexcept;
        LintS   operator -   (const LintS& target) const noexcept;
        LintS   operator *   (const LintS& target) const noexcept;
        LintS   operator /   (const LintS& target) const noexcept;
        LintS   operator %   (const LintS& target) const noexcept;

        /**
        * @brief Returns value of number as string.
        */
        std::string toString() const noexcept;

        LintS();
        LintS(const size_t& index);
        LintS(LintS && target) noexcept = default;
        LintS(const LintS & target);
        virtual ~LintS() = default;
    };
}

#endif // LINT_H_INCLUDED
