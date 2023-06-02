#ifndef PARKA_UTIL_POOL_HPP
#define PARKA_UTIL_POOL_HPP

#include "parka/util/Arena.hpp"

#include <cassert>
#include <type_traits>
#include <utility>

namespace parka
{
	template <typename T>
	class Pool
	{

		Arena _arena;

	public:

		Pool(usize maxItemCount) :
		_arena(sizeof(T) * maxItemCount)
		{}
		Pool(Pool&&) = default;
		Pool(const Pool&) = delete;
		~Pool()
		{
			if constexpr (!std::is_trivially_destructible_v<T>)
			{
				usize length = count();
				auto *data = (T*)_arena.data();

				for (usize i = 0; i < length; ++i)
					data[i].~T();
			}
		}

		usize add(T&& value)
		{
			auto index = count();
			auto *item = _arena.allocate(sizeof(T));

			new (item) auto(std::move(value));

			return index;
		}

		void fill(usize newLength, const T& fillValue)
		{
			static_assert(std::is_copy_assignable_v<T>, "Value must be copy assignable to fill with default value");

			_arena.reserve(newLength * sizeof(T));

			auto *data = (T*)_arena.data();
			auto length = _arena.bytesUsed() / sizeof(T);

			for (usize i = 0; i < length; ++i) 
				data[i] = fillValue;
		}

		usize getIndex(const T *ptr) const { return _arena.getOffset((byte*)ptr) / sizeof(T); }

		T& operator[](usize index) { assert(index < count()); return ((T*)_arena.data())[index]; }
		const T& operator[](usize index) const { assert(index < count()); return ((T*)_arena.data())[index]; }
		T* begin() { return (T*)_arena.begin(); }
		T* end() { return (T*)_arena.end(); }
		const T* begin() const { return (const T*)_arena.begin(); }
		const T* end() const { return (const T*)_arena.end(); }

		usize count() const { return _arena.bytesUsed() / sizeof(T); }
	};
}

#endif
