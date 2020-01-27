#include "nlib/utility/lint.h"

#include <iostream>

namespace Nlib
{
    uint64_t & LintStorage::operator[] (const size_t& index) const noexcept
    {
        return _storage[index % _msize];
    }
    size_t LintStorage::size() const noexcept
    {
        return _msize;
    }
    size_t LintStorage::size(const size_t& index)
    {
        if (index != _msize)
        {
            if (_storage != nullptr)
                delete[] _storage;
            _msize = index / sizeof(uint64_t);
            if (_msize * sizeof(uint64_t) < index)
                _msize += 1;
            _storage = new uint64_t[_msize];
        }
        return _msize;
    }

    LintStorage & LintStorage::operator = (const LintStorage & target)
    {
        if (_msize!=target._msize)
        {
            if (_storage != nullptr)
            {
                delete[] _storage;
            }
            _storage = new uint64_t[target._msize];
        }
        _size = target._size;
        std::memcpy(_storage,target._storage,_msize * sizeof(uint64_t));
        return *this;
    }

    LintStorage& LintStorage::operator = (LintStorage&& target)
    {
        if (_storage != nullptr)
        {
            delete[] _storage;
        }
        _storage = std::move(target._storage);
        _size = std::move(target._size);
        return *this;
    }

    LintStorage::LintStorage() noexcept
    {
        _size = 0;
        _storage = nullptr;
    }
    LintStorage::LintStorage(const size_t& index)
    {
        _msize = index / sizeof(uint64_t);
        if (_msize * sizeof(uint64_t) < index)
            _msize += 1;
        _storage = new uint64_t[_msize];
        std::memset(_storage,0,_msize * sizeof(uint64_t));
    }

    LintStorage::LintStorage(const LintStorage & target)
    {
        _size = target._size;
        if (_msize > 0)
        {
            _storage = new uint64_t[_msize];
            std::memcpy(_storage,target._storage,_msize*sizeof(uint64_t));
        }
        else
        {
            _storage = nullptr;
        }
    }

    LintStorage::LintStorage(LintStorage && target) noexcept:_size(std::move(target._size)),_storage(std::move(target._storage))
    {
        target._storage=nullptr;
        target._size=0;
    }

    LintStorage::~LintStorage()
    {
        if (_storage != nullptr)
            delete[] _storage;
    }


    LintS & LintS::operator = (const uint64_t& target) noexcept
    {
        _storage[0]=target;
        for (size_t i=1; i<_storage.size(); ++i)
            _storage[i]=0;
        return *this;
    }
    LintS & LintS::operator = (const LintS& target) noexcept
    {
        const size_t siz = std::min(_storage.size(),target._storage.size());
        for (size_t i = 0; i < siz; ++i)
            _storage[i] = target._storage[i];
        for (size_t i = siz; i < _storage.size(); ++i)
            _storage[i] = 0;
        return *this;
    }

    bool LintS::operator == (const LintS& target) const noexcept
    {
        const size_t siz = std::min(target._storage.size(),_storage.size());
        for (size_t i = 0; i < siz; ++i)
            if (_storage[i] != target._storage[i])
                return std::move(false);
        if (_storage.size() > siz && _storage[siz] > 0)
            return std::move(false);
        return std::move(true);
    }

    bool LintS::operator < (const LintS& target) const noexcept
    {
        const size_t siz = std::min(target._storage.size(),_storage.size());
        const size_t rest = std::max(target._storage.size(),_storage.size()) - siz;
        if (target._storage.size()>_storage.size())
        {
            for (size_t i = siz; i < siz+rest; ++i)
                if (target._storage[i-1] > 0)
                    return std::move(true);
        }
        else
        {
            for (size_t i = siz; i < siz+rest; ++i)
                if (_storage[i-1] > 0)
                    return std::move(false);
        }
        for (size_t i = siz; i > 0; --i)
        {
            if (_storage[i-1] > target._storage[i-1])
                return std::move(false);
            else if (_storage[i-1] < target._storage[i-1])
                return std::move(true);
        }
        return std::move(false);
    }

    bool LintS::operator <= (const LintS& target) const noexcept
    {
        const size_t siz = std::min(target._storage.size(),_storage.size());
        const size_t rest = std::max(target._storage.size(),_storage.size()) - siz;
        if (target._storage.size()>_storage.size())
        {
            for (size_t i = siz; i < siz+rest; ++i)
                if (target._storage[i-1] > 0)
                    return std::move(true);
        }
        else
        {
            for (size_t i = siz; i < siz+rest; ++i)
                if (_storage[i-1] > 0)
                    return std::move(false);
        }
        for (size_t i = siz; i > 0; --i)
        {
            if (_storage[i-1] > target._storage[i-1])
                return std::move(false);
            else if (_storage[i-1] < target._storage[i-1])
                return std::move(true);
        }
        return std::move(true);
    }

    bool LintS::operator > (const LintS& target) const noexcept
    {
        const size_t siz = std::min(target._storage.size(),_storage.size());
        const size_t rest = std::max(target._storage.size(),_storage.size()) - siz;
        if (target._storage.size() > _storage.size())
        {
            for (size_t i = siz; i < siz+rest; ++i)
                if (target._storage[i] > 0)
                    return std::move(false);
        }
        else
        {
            for (size_t i = siz; i < siz+rest; ++i)
                if (_storage[i] > 0)
                    return std::move(true);
        }
        for (size_t i = siz; i > 0; --i)
        {
            if (_storage[i-1] < target._storage[i-1])
                return std::move(false);
            else if (_storage[i-1] > target._storage[i-1])
                return std::move(true);
        }
        return std::move(false);
    }

    bool LintS::operator >= (const LintS& target) const noexcept
    {
        const size_t siz = std::min(target._storage.size(),_storage.size());
        const size_t rest = std::max(target._storage.size(),_storage.size()) - siz;
        if (target._storage.size()>_storage.size())
        {
            for (size_t i = siz; i < siz+rest; ++i)
                if (target._storage[i] > 0)
                    return std::move(false);
        }
        else
        {
            for (size_t i = siz; i < siz+rest; ++i)
                if (_storage[i] > 0)
                    return std::move(true);
        }
        for (size_t i = siz; i > 0; --i)
        {
            if (_storage[i-1] < target._storage[i-1])
                return std::move(false);
            else if (_storage[i-1] > target._storage[i-1])
                return std::move(true);
        }
        return std::move(true);
    }

    LintS & LintS::operator <<= (const size_t& index) noexcept
    {
        uint64_t mask1 = 0,mask2 = 0;
        for (size_t i = _storage.size(); i > 0; --i)
        {
            mask1 = _storage[i-1] << (index % true_size);
            mask2 = _storage[i-1] >> (true_size - index % true_size);
            mask2 *= (index % true_size != 0);
            if (i + index / true_size < _storage.size()+1 )
            {
                _storage[i+index / true_size-1] = mask1;
                if (i +1 + index / true_size < _storage.size()+1 )
                    _storage[i +1 +index / true_size-1] |= mask2;
            }
        }
        if (index / true_size > 0)
            _storage[0] = 0;
        return *this;
    }
    LintS & LintS::operator >>= (const size_t& index) noexcept
    {
        uint64_t mask1 = 0,mask2 = 0;
        for (size_t i = 0; i < _storage.size(); ++i)
        {
            mask1 = _storage[i] >> (index % true_size);
            mask2 = _storage[i] << (true_size - index % true_size);
            if (i >= index / true_size)
            {
                _storage[i - index / true_size] = mask1;
                if (i >= index / true_size+1)
                    _storage[i -1 - index / true_size] |= mask2;
            }
        }
        return *this;
    }

    LintS & LintS::operator += (const LintS& target) noexcept
    {
        const size_t siz = std::min(_storage.size(),target._storage.size());
        bool ov1 = false,ov2 = false;
        uint64_t d = 0;
        for (size_t i = 0; i < siz; ++i)
        {
            d = nu - _storage[i];
            ov2 = d < target._storage[i];
            ov2 += (ov1 && d == target._storage[i]);
            _storage[i] += target._storage[i] + ov1;
            ov1 = ov2;
        }
        for (size_t i = siz; i < _storage.size(); ++i)
        {
            if (!ov1)
                break;
            ov2 = _storage[i] == nu;
            _storage[i] += ov1;
            ov1 = ov2;
        }
        return *this;
    }
    LintS & LintS::operator -= (const LintS& target) noexcept
    {
        const size_t siz=std::min(_storage.size(),target._storage.size());
        bool un1=false,un2=false;
        for (size_t i=0; i<siz; ++i)
        {
            un2=_storage[i]<target._storage[i];
            un2+=(un1 && _storage[i]==target._storage[i]);
            _storage[i]-=target._storage[i];
            _storage[i]-=un1;
            un1=un2;
        }
        for (size_t i=siz; i<_storage.size(); ++i)
        {
            if (!un1)
                break;
            un2=_storage[i]==0;
            _storage[i]-=un1;
            un1=un2;
        }
        return *this;
    }

    LintS & LintS::operator *= (const LintS& target) noexcept
    {
        ///\todo redo all
        LintS tmp(*this);

        *this=0;

        for (unsigned int i=_storage.size()*sizeof(uint64_t)*8; i>0; --i)
        {
            this->operator<<=(1);
            if ((tmp._storage[(i-1) / (sizeof(uint64_t)*8)] >> ((i-1) % (sizeof(uint64_t)*8))) & 1)
            {
                this->operator+=(target);
            }
        }
        return *this;
    }

    LintS & LintS::operator /= (const LintS& target) noexcept
    {
        bool zer = true;
        for (size_t i = 0; i < target._storage.size(); ++i)
            if (target._storage[i] != 0)
                zer = false;
        if (zer)
            return *this;
        LintS tmp(*this);
        bool x = false;
        LintS res(_storage.size()*sizeof(uint64_t));
        for (size_t i = 0; i < _storage.size(); ++i)
            _storage[i] = 0;
        for (size_t i = _storage.size() * 8 * sizeof(uint64_t); i > 0; --i)
        {
            res <<= 1;
            x = (tmp._storage[(i-1) / (sizeof(uint64_t)*8)] >> ((i-1) % (sizeof(uint64_t)*8))) & 1;
            res._storage[0] ^= (-x ^ res._storage[0]) & 1;
            if (res >= target)
            {
                res -= target;
                _storage[(i-1) / (sizeof(uint64_t)*8)] |= (1ULL << ((i-1) % (sizeof(uint64_t)*8)));
            }
        }
        return *this;
    }

    LintS & LintS::operator %= (const LintS& target) noexcept
    {
        bool zer = true;
        for (size_t i = 0; i < target._storage.size(); ++i)
            if (target._storage[i] != 0)
                zer = false;
        if (zer)
            return *this;
        LintS tmp(*this);
        bool x = false;
        for (size_t i = 0; i < _storage.size(); ++i)
            _storage[i] = 0;
        for (size_t i = _storage.size() * 8 * sizeof(uint64_t); i > 0; --i)
        {
            this->operator <<= (1);
            x = (tmp._storage[(i-1) / (sizeof(uint64_t)*8)] >> ((i-1) % (sizeof(uint64_t)*8))) & 1;
            _storage[0] ^= (-x ^ _storage[0]) & 1;
            if (this->operator >= (target))
            {
                this->operator -= (target);
            }
        }
        return *this;
    }

    LintS LintS::operator + (const LintS& target) const noexcept
    {
        return LintS(*this) += target;
    }

    LintS LintS::operator - (const LintS& target) const noexcept
    {
        return LintS(*this) -= target;
    }

    LintS LintS::operator * (const LintS& target) const noexcept
    {
        return LintS(*this) *= target;
    }

    LintS LintS::operator / (const LintS& target) const noexcept
    {
        return LintS(*this) /= target;
    }

    LintS LintS::operator % (const LintS& target) const noexcept
    {
        return LintS(*this) %= target;
    }

    std::string LintS::toString() const noexcept
    {
        LintS a(*this);
        std::string ret;
        LintS zero(8),t(8),c(a.size);
        zero = 0;
        t = max10pow();
        uint64_t r = 0,counter = 0;
        unsigned int cc=0;
        while (a > zero)
        {
            std::cout << "_" << cc << std::endl;
            ++cc;
            c = a;
            c %= t;
            a /= t;
            r = c._storage[0];
            counter = 0;
            while (r > 0)
            {
                ret += '0' + (r%10);
                r /= 10;
                ++counter;
            }
            if (a > zero)
            {
                for (unsigned int i = counter; i < max10digits(); ++i)
                {
                    ret+='0';
                }
            }
        }
        char tmp = 0;
        for (unsigned int i = 0; i < ret.size() / 2; ++i)
        {
            tmp = ret[i];
            ret[i] = ret[ret.size()-1-i];
            ret[ret.size()-1-i] = tmp;
        }
        return ret;
    }

    LintS::LintS() :_storage(8), size(8) {/**/}
    LintS::LintS(const size_t& index) :_storage(index), size(index) {/**/}
    LintS::LintS(const LintS & target) :_storage(target._storage), size(target.size) {/**/}
}
