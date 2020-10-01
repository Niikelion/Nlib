#include <nlib/threading/buffers.hpp>

namespace Nlib
{
	namespace Threading
	{
		CyclicIndex& CyclicIndex::operator++() noexcept
		{
			index++;
			return *this;
		}
		bool CyclicIndex::operator==(const CyclicIndex& t) const noexcept
		{
			return t.index == index;
		}
		bool CyclicIndex::operator>(const CyclicIndex& t) const noexcept
		{
			constexpr uint16_t uint8max = ~static_cast<uint8_t>(0), uint8maxWrapped = ~static_cast<uint16_t>(0) - uint8max;
			return (index < uint8max && t.index > uint8maxWrapped) ? true : index > t.index;
		}
		bool CyclicIndex::operator>=(const CyclicIndex& t) const noexcept
		{
			return *this == t || *this > t;
		}
	}
}