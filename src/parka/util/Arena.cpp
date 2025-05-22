#include "parka/util/Arena.hpp"
#include "parka/util/Common.hpp"

#include <stdexcept>
#include <cassert>
#include <string>

#ifdef _WIN32
#include <windows.h>
#include <winnt.h>
//#include <memoryapi.h>
#else
#include <unistd.h>
#include <sys/mman.h>
#endif

#ifdef _WIN32
#define ALLOCATION_FAILED (nullptr)
#define PROTECTION_FAILED (0)
#else
#define ALLOCATION_FAILED (MAP_FAILED)
#define PROTECTION_FAILED (-1)
#endif

// TODO: Cross platform includes

namespace parka
{
	static usize getPageSize()
	{
		static usize pageSize;

		if (pageSize == 0)
		{
			#ifndef _WIN32

			pageSize = sysconf(_SC_PAGESIZE);
			
			#else

			SYSTEM_INFO systemInfo;

			GetSystemInfo(&systemInfo);

			pageSize = systemInfo.dwPageSize;

			#endif
		}

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
		byte* data;

		#ifndef _WIN32

		data = (byte*)mmap(nullptr, maxCapacity, PROT_NONE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

		#else

		data = (byte*)VirtualAlloc(NULL, maxCapacity, MEM_RESERVE, PAGE_NOACCESS);		

		#endif
		
		if (data == ALLOCATION_FAILED)
			throw std::runtime_error("Failed to allocate Arena with max capacity of " + std::to_string(maxCapacity) + " bytes.");

		return data;
	}

	static void deallocateArena(byte *data, const usize length)
	{
		#ifdef _WIN32

		VirtualFree(data, length, MEM_RELEASE);

		#else

		munmap(data, length);

		#endif
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

			#ifdef _WIN32

			DWORD oldProtect;

			auto result = VirtualProtect(startOfRegion, bytesToCommit, PAGE_READWRITE, &oldProtect);
			
			// Could use getlasterror

			#else
			
			auto result = mprotect(startOfRegion, bytesToCommit, PROT_READ | PROT_WRITE);
			
			#endif

			if (result == PROTECTION_FAILED)
				abort();
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

		const auto offset = (usize)(ptr - _data);

		return offset;
	}
}
