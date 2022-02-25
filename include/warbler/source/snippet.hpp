#ifndef WARBLER_SOURCE_TEXT_HPP
#define WARBLER_SOURCE_TEXT_HPP

#include <warbler/source/file.hpp>

namespace warbler::source
{
	class Snippet
	{
	private:

		const File& _file;
		usize _offset;
		usize _start_pos;
		usize _end_pos;
		usize _length;
		usize _line;
		usize _col;

	public:

		Snippet(const File& file, usize pos, usize length);

		char operator[](usize i) const { return _file[i - _offset]; }

		const String& filename() const { return _file.filename(); }
		usize length() const { return _length; }
		usize start_pos() const { return _start_pos; }
		usize end_pos() const { return _end_pos; }
		usize line() const { return _line; }
		usize col() const { return _col; }
	};
}

#endif
