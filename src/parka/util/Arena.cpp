
#include "parka/log/Log.hpp"
#include "parka/util/Common.hpp"
#include "parka/util/Print.hpp"
#include "parka/util/Arena.hpp"

#include <exception>
#include <new>
#include <stdexcept>
#include <unistd.h>

// TODO: Cross platform includes
#include <sys/mman.h>

namespace parka
{
	static usize getPageSize()
	{
		// TODO: Make getPageSize() platform
		static usize pageSize;

		if (pageSize == 0)
			pageSize = sysconf(_SC_PAGESIZE);

		return pageSize;
	}

	static usize getPageAlignedLength(const usize length)
	{
		const usize pageSize = getPageSize();
		const bool hasPageRemainder = length % pageSize > 0;
		const usize extraPages = (usize)hasPageRemainder;
		const usize pageCount = length / pageSize + extraPages;
		const usize pageAlignedLength = pageCount * pageSize;

		return pageAlignedLength;
	}

	static byte *allocateArena(const usize maxCapacity)
	{
		// TODO: make allocateArena() cross platform
		auto * const data = (byte*)mmap(nullptr, maxCapacity, PROT_NONE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

		if (data == MAP_FAILED)
			throw std::runtime_error("Failed to allocate Arena with max capacity of " + std::to_string(maxCapacity) + " bytes.");

		return data;
	}

	// TODO: Implement reallocateArena

	static void deallocateArena(byte *data, const usize length)
	{
		munmap(data, length);
	}

	Arena::Arena(usize maxCapacity):
		_maxCapacity(getPageAlignedLength(maxCapacity)),
		_capacity(0),
		_length(0),
		_data(allocateArena(_maxCapacity))
	{}

	Arena::~Arena()
	{
		const usize reservedByteCount = _maxCapacity;

		deallocateArena(_data, reservedByteCount);
	}

	byte *Arena::allocate(const usize length)
	{
		assert(_maxCapacity > 0);

		const usize newLength = _length + length;

		// TODO: Implement reallocation if newLength > _maxCapacity

		if (newLength > _capacity)
		{
			const usize bytesToCommit = getPageAlignedLength(newLength - _capacity);
			auto *startOfRegion = _data + _capacity;
			const auto code = mprotect(startOfRegion, bytesToCommit, PROT_READ | PROT_WRITE);

			if (code == -1)
				log::fatal("Failed to commit $ bytes in Arena.", bytesToCommit);
		}

		auto * const ptr = _data + _length;

		_length = newLength;

		return ptr;
	}

	void Arena::reserve(const usize length)
	{
		if (_length >= length)
			return;

		const usize difference = length - _length;

		allocate(difference);
	}

	usize Arena::getOffset(const byte * const ptr) const
	{
		assert(ptr >= _data);
		assert(ptr < _data + _length);

		const auto offset = ptr - _data;

		return offset;
	}
}
