#ifndef PARKA_UTIL_STRING_VIEW_HPP
#define PARKA_UTIL_STRING_VIEW_HPP

#include "parka/util/String.hpp"
#include <ostream>
namespace parka
{
	class StringView
	{
		const char *_ptr;
		usize _length;

	public:
		


		StringView(const char *ptr, usize length) :
		_ptr(ptr),
		_length(length)
		{}

		StringView from(const char *text, usize index, usize length);
		StringView from(const String& text, usize index, usize length);

		const auto *ptr() const {	return _ptr; }
		const auto& length() const { return _length; }
		const char *begin() const { return _ptr; }
		const char *end() const { return _ptr + _length; }
		const char& operator[](usize index) const { assert(index < _length); return _ptr[index]; }

		friend std::ostream& operator<<(std::ostream& out, const StringView& text);
	};
}

#endif
