#ifndef PARKA_UTIL_VIEW_HPP
#define PARKA_UTIL_VIEW_HPP

#include "parka/util/Primitives.hpp"

#include <cassert>

namespace parka
{
	template <typename T>
	class View
	{
		T *_data;
		usize _size;

	public:

		View(T *data, usize size) :
		_data(data),
		_size(size)
		{
			assert(data != nullptr);
		}
		View(View&&) = default;
		View(const View&) = default;
		View() = default;

		T& operator[](usize index) { assert(index < _size); return _data[index]; }
		const T& operator[](usize index) const { assert(index < _size); return _data[index]; }
		T *begin() { return &_data[0]; }
		const T *begin() const { return &_data[0]; }
		T *end() { return &_data[_size]; }
		const T *end() const { return &_data[_size]; }
	};
}

#endif
