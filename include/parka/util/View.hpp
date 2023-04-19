#ifndef PARKA_UTIL_VIEW_HPP
#define PARKA_UTIL_VIEW_HPP

#include "parka/util/Common.hpp"

#include <cassert>

namespace parka
{
	template <typename T>
	class View
	{
		const T *_data;
		usize _size;

	public:

		View(const T *data, usize size) :
		_data(data),
		_size(size)
		{
			assert(data != nullptr);
		}
		View(View&&) = default;
		View(const View&) = default;
		View() = default;

		const T& operator[](usize index) const { assert(index < _size); return _data[index]; }
		const T *begin() const { return &_data[0]; }
		const T *end() const { return &_data[_size]; }
	};
}

#endif
