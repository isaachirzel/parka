
#include "parka/util/Print.hpp"
#include "parka/util/Arena.hpp"

#include <cassert>
#include <exception>
#include <new>
#include <unistd.h>
// TODO: Make this cross platform
#include <sys/mman.h>

namespace parka
{
	usize pageSize = 0;

	usize getPageAlignedByteCount(usize bytes)
	{
		usize difference = bytes % pageSize;

		if (difference > 0)
			bytes = (bytes - difference) + pageSize;

		return bytes;
	}

	Arena::Arena(usize minBytes)
	{
		if (pageSize == 0)
			pageSize = getpagesize();

		usize bytes = getPageAlignedByteCount(minBytes);
		_pageCount = bytes / pageSize;
		_data = (byte*)mmap(nullptr, bytes, PROT_NONE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

		if (_data == MAP_FAILED)
			throw std::bad_alloc();
	}

	Arena::~Arena()
	{
		usize mappingLength = _pageCount * pageSize;

		munmap(_data, mappingLength);
	}

	void *Arena::allocate(usize bytes)
	{
		assert(_pageCount > 0);

		usize committedBytes = _committedPages * pageSize;
		usize requiredBytes = _bytesUsed + bytes;

		if (requiredBytes > committedBytes)
		{
			usize minBytesToCommit = requiredBytes - committedBytes;
			usize pagesToCommit = minBytesToCommit / pageSize;

			if (minBytesToCommit % pageSize > 0)
				pagesToCommit += 1;

			void *startOfPagesToCommit = _data + (_committedPages * pageSize);
			usize bytesToCommit = pagesToCommit * pageSize;
			int code = mprotect(startOfPagesToCommit, bytesToCommit, PROT_READ | PROT_WRITE);

			if (code == -1)
			{
				exitWithError("Failed to commit $ pages in Arena.", pagesToCommit);
			}
		}

		void *ptr = _data + _bytesUsed;

		_bytesUsed += bytes;

		return ptr;
	}

	void *Arena::reserve(usize bytes)
	{
		if (_bytesUsed >= bytes)
			return end();

		usize difference = bytes - _bytesUsed;
		auto *data = allocate(difference);

		return data;
	}

	usize Arena::getOffset(byte *ptr) const
	{
		assert(ptr >= _data);
		assert(ptr < _data + _bytesUsed);

		auto offset = ptr - _data;

		return offset;
	}
}
