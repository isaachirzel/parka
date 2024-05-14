#ifndef PARKA_UTIL_ARENA_HPP
#define PARKA_UTIL_ARENA_HPP

#include "parka/util/Common.hpp"

namespace parka
{
	class Arena
	{
		usize _maxCapacity;
		usize _capacity;
		usize _length;
		byte *_data;

	public:

		Arena(usize maxCapacity);
		Arena(Arena&&) = default;
		Arena(const Arena&) = delete;
		~Arena();

		byte *allocate(const usize length);
		void reserve(const usize length);
		usize getOffset(const byte * const ptr) const;

		auto *data() { return _data; }
		const auto *data() const { return _data; }
		const auto& maxCapacity() const { return _maxCapacity; }
		const auto& capacity() const { return _capacity; }
		const auto& length() const { return _length; }
		auto *begin() { return _data; }
		auto *end() { return _data + _length; }
		const auto *begin() const { return _data; }
		const auto *end() const { return _data + _length; }
	};
}

#endif
