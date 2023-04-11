#ifndef PARKA_UTIL_ARENA_HPP
#define PARKA_UTIL_ARENA_HPP

#include "parka/util/Primitives.hpp"

namespace parka
{
	class Arena
	{
		void *_data;
		usize _pageCount;
		usize _committedPages;
		usize _bytesUsed;

	public:

		Arena(usize minByteCount);
		Arena(Arena&&) = default;
		Arena(const Arena&) = delete;
		~Arena();

		void *allocate(usize bytes);
		usize getOffset(void *ptr) const;

		auto *data() { return _data; }
		const auto *data() const { return _data; }
		const auto& pageCount() const { return _pageCount; }
		const auto& committedPages() const { return _committedPages; }
		const auto& bytesUsed() const { return _bytesUsed; }
	};
}

#endif
