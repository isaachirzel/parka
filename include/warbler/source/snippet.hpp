#ifndef WARBLER_SOURCE_TEXT_HPP
#define WARBLER_SOURCE_TEXT_HPP

#include <warbler/source/file.hpp>

namespace warbler::source
{
	class Snippet
	{
	private:

		String _filename;
		Array<String> _lines;
		usize _start_pos;
		usize _end_pos;
		usize _line;
		usize _col;

	public:

		Snippet(const File& file, usize pos, usize length);

		const String& filename() const { return _filename; }
		const Array<String>& lines() const { return _lines; }
		usize start_pos() const { return _start_pos; }
		usize end_pos() const { return _end_pos; }
		usize line() const { return _line; }
		usize col() const { return _col; }
	};
}

#endif
