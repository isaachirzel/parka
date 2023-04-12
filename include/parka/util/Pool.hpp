#ifndef PARKA_UTIL_POOL_HPP
#define PARKA_UTIL_POOL_HPP

#include "parka/util/Arena.hpp"
#include "parka/util/View.hpp"

#include <cassert>
#include <utility>

namespace parka
{
	template <typename T>
	class Pool
	{
		Arena _arena;
		usize _itemCount;

	public:

		Pool(usize maxItemCount) :
		_arena(sizeof(T) * maxItemCount), // FIXME: Add size of
		_itemCount(0)
		{}
		Pool(Pool&&) = default;
		Pool(const Pool&) = delete;
		~Pool() = default;

		usize add(T&& value)
		{
			auto index = _itemCount;
			auto *item = _arena.allocate(sizeof(T));

			new (item) auto(std::move(value));

			_itemCount += 1;

			return index;
		}

		usize getIndex(T *ptr) const { return _arena.getOffset(ptr) / sizeof(T); }

		T& operator[](usize index) { assert(index < _itemCount); return ((T*)_arena.data())[index]; }
		const T& operator[](usize index) const { assert(index < _itemCount); return ((T*)_arena.data())[index]; }

		View<T> items() { return View((T*)_arena.data(), _itemCount); }
		usize count() const { return _itemCount; }
	};
}

#endif