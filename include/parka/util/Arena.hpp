#ifndef PARKA_UTIL_ARENA_HPP
#define PARKA_UTIL_ARENA_HPP

#include "parka/util/Common.hpp"

namespace parka
{
	class Arena
	{
		const usize _pageSize;
		usize _reservedPageCount;
		usize _committedPageCount;
		usize _usedByteCount;
		byte *_data;

	public:

		Arena(usize length);
		Arena(Arena&&) = default;
		Arena(const Arena&) = delete;
		~Arena();

		void *allocate(const usize length);
		void reserve(const usize length);
		usize getOffset(const byte * const ptr) const;

		auto *data() { return _data; }
		const auto *data() const { return _data; }
		const auto& pageCount() const { return _reservedPageCount; }
		const auto& committedPages() const { return _committedPageCount; }
		const auto& bytesUsed() const { return _usedByteCount; }
		auto *begin() { return _data; }
		auto *end() { return _data + _usedByteCount; }
		const auto *begin() const { return _data; }
		const auto *end() const { return _data + _usedByteCount; }
	};
}

#endif
