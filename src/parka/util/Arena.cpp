
#include "parka/log/Log.hpp"
#include "parka/util/Common.hpp"
#include "parka/util/Print.hpp"
#include "parka/util/Arena.hpp"

#include <cassert>
#include <exception>
#include <new>
#include <unistd.h>

// TODO: Cross platform includes
#include <sys/mman.h>

namespace parka
{
	usize getPageSize()
	{
		// TODO: Make getPageSize() platform
		static usize pageSize;

		if (pageSize == 0)
			pageSize = getpagesize();

		return pageSize;
	}

	usize getReservedPageCount(usize minBytes, usize pageSize)
	{
		const bool hasPageRemainder = minBytes % pageSize > 0;
		usize pageCount = minBytes / pageSize;

		if (hasPageRemainder)
			pageCount += 1;

		return pageCount;
	}

	byte *allocateArena(usize pageCount, usize pageSize)
	{
		// TODO: make allocateArena() cross platform
		const auto byteCount = pageCount * pageSize;
		auto * const data = (byte*)mmap(nullptr, byteCount, PROT_NONE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

		if (data == MAP_FAILED)
			Log::fatal("Failed to allocate $ bytes.", byteCount);

		return data;
	}

	// TODO: Implement reallocateArena

	void deallocateArena(byte *data, const usize length)
	{
		munmap(data, length);
	}

	Arena::Arena(usize length) :
	_pageSize(getPageSize()),
	_reservedPageCount(getReservedPageCount(length, _pageSize)),
	_committedPageCount(0),
	_usedByteCount(0),
	_data(allocateArena(_reservedPageCount, _pageSize))
	{}

	Arena::~Arena()
	{
		const usize reservedByteCount = _reservedPageCount * _pageSize;

		deallocateArena(_data, reservedByteCount);
	}

	void *Arena::allocate(const usize length)
	{
		assert(_reservedPageCount > 0);

		const usize committedByteCount = _committedPageCount * _pageSize;
		const usize requiredByteCount = _usedByteCount + length;

		// TODO: Implement reallocation if the arena fills up

		if (requiredByteCount > committedByteCount)
		{
			const usize minBytesToCommit = requiredByteCount - committedByteCount;
			const bool hasPageRemainder = minBytesToCommit % _pageSize > 0;
			const usize pagesToCommit = minBytesToCommit / _pageSize + hasPageRemainder;

			auto * const startOfPagesToCommit = _data + (_committedPageCount * _pageSize);
			const auto bytesToCommit = pagesToCommit * _pageSize;
			const auto code = mprotect(startOfPagesToCommit, bytesToCommit, PROT_READ | PROT_WRITE);

			if (code == -1)
				Log::fatal("Failed to commit $ pages in Arena.", pagesToCommit);
		}

		auto * const ptr = _data + _usedByteCount;

		_usedByteCount = requiredByteCount;

		return ptr;
	}

	void Arena::reserve(const usize length)
	{
		if (_usedByteCount >= length)
			return;

		const usize difference = length - _usedByteCount;

		allocate(difference);
	}

	usize Arena::getOffset(const byte * const ptr) const
	{
		assert(ptr >= _data);
		assert(ptr < _data + _usedByteCount);

		const auto offset = ptr - _data;

		return offset;
	}
}
