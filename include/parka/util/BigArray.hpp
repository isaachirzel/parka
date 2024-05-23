#ifndef PARKA_UTIL_BIG_ARRAY_HPP
#define PARKA_UTIL_BIG_ARRAY_HPP

#include "parka/util/Arena.hpp"

namespace parka
{
	template <typename T>
	class BigArray
	{
		Arena _arena;
		usize _length;

	public:

		BigArray(usize capacity):
			_arena(capacity * sizeof(T)),
			_length(0)
		{}
		BigArray(BigArray&& other) = default;
		BigArray(const BigArray&) = delete;

		T& push(T&& value)
		{
			const auto newLength = _length + 1;
			const auto arenaLength = _arena.length() / sizeof(T);
			const auto diff = newLength - arenaLength;

			if (diff > 0)
				_arena.allocate(diff * sizeof(T));

			auto* elements = data();
			auto* ptr = &elements[_length];

			new (ptr) T(std::move(value));

			_length = newLength;

			return *ptr;
		}

		void truncate(const usize newLength)
		{
			assert(newLength <= _length);

			if (_length == newLength)
				return;

			auto* data = begin();

			for (usize i = newLength; i < _length; ++i)
				data[i].~T();

			_length = newLength;
		}

		T& operator[](usize index) { assert(index < _length); return ((T*)_arena.data())[index]; }
		const T& operator[](usize index) const { assert(index < _length); return ((T*)_arena.data())[index]; }
		T* data() { return (T*)_arena.data(); }
		T* begin() { return (T*)_arena.begin(); }
		T* end() { return (T*)_arena.begin() + _length; }
		const T* data() const { return (const T*)_arena.data(); }
		const T* begin() const { return (const T*)_arena.begin(); }
		const T* end() const { return (const T*)_arena.end() + _length; }
		const auto& length() const { return _length; }
		usize capacity() const { return _arena.capacity() / sizeof(T); }
	};
}

#endif
