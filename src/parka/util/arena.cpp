
#include "parka/util/print.hpp"
#include "parka/util/arena.hpp"

#include <cassert>

// TODO: Make this OS agnostic
#include <exception>
#include <new>
#include <unistd.h>
#include <sys/mman.h>

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
	_data = mmap(NULL, bytes, PROT_NONE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

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

		void *startOfPagesToCommit = (char*)_data + (_committedPages * pageSize);
		usize bytesToCommit = pagesToCommit * pageSize;
		int code = mprotect(startOfPagesToCommit, bytesToCommit, PROT_READ | PROT_WRITE);

		if (code == -1)
		{
			exitWithError("Failed to commit $ pages in Arena.", pagesToCommit);
		}
	}

	void *ptr = (char*)_data + _bytesUsed;

	_bytesUsed += bytes;

	return ptr;
}

usize Arena::getOffset(void *ptr) const
{
	assert(ptr >= _data);
	assert(ptr < (char*)_data + _bytesUsed);

	auto offset = (char*)ptr - (char*)_data;

	return offset;
}
