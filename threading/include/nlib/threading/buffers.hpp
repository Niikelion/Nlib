#pragma once

#include <atomic>

namespace Nlib
{
	namespace Threading
	{
		class CyclicIndex
		{
		public:
			CyclicIndex& operator ++ () noexcept;
			bool operator == (const CyclicIndex& t) const noexcept;
			bool operator > (const CyclicIndex& t) const noexcept;
			bool operator >= (const CyclicIndex& t) const noexcept;

			CyclicIndex() : index(0) {}
			CyclicIndex(const CyclicIndex&) = default;
		private:
			uint32_t index;
		};

		template<typename T> class TrippleBuffer
		{
		public:
			T& nextWriteBuffer() noexcept
			{
				write_p = exchange_p.exchange(write_p);
				return *write_p;
			}
			T& currentWriteBuffer() noexcept
			{
				return *write_p;
			}

			T& nextReadBuffer() noexcept
			{
				read_p = exchange_p.exchange(read_p);
				return *read_p;
			}
			T& currentReadBuffer() noexcept
			{
				return *read_p;
			}

			bool isLockless() const noexcept
			{
				return exchange_p.is_lock_free();
			}

			TrippleBuffer() : write_p(&first), read_p(&third), exchange_p(&second) {}
		private:
			T first, second, third;
			T* write_p;
			T* read_p;
			std::atomic<T*> exchange_p;
		};
	}
}