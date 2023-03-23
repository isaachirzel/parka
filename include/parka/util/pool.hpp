#ifndef PARKA_UTIL_POOL_HPP
#define PARKA_UTIL_POOL_HPP

#include "parka/util/arena.hpp"
#include "parka/util/view.hpp"

#include <cassert>

template <typename T>
class Pool
{
	Arena _arena;
	usize _itemCount;

public:

	Pool(usize maxItemCount) :
	_arena(maxItemCount), // FIXME: Add size of
	_itemCount(0)
	{}
	Pool(Pool&&) = default;
	Pool(const Pool&) = delete;
	~Pool() = default;

	T* add(usize count);
	T& add();

	T& operator[](usize index) { assert(index < _itemCount); return ((T*)_arena.data())[index]; }
	const T& operator[](usize index) const { assert(index < _itemCount); return ((T*)_arena.data())[index]; }

	View<T> items() { return View((T*)_arena.data(), _itemCount); }
	usize count() const { return _itemCount; }
};

#endif
