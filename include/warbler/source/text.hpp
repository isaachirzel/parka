#ifndef WARBLER_SOURCE_TEXT_HPP
#define WARBLER_SOURCE_TEXT_HPP

#include <warbler/util/string.hpp>
#include <warbler/util/primitive.hpp>

namespace warbler::source
{
	class Snippet
	{
	private:

		String _filename;
		String _data;
		usize _pos;
		usize _length;
		usize _line;
		usize _col;

	public:

		Snippet(String&& filename, String&& data, usize pos, usize length, usize line, usize col);

		const String& filename() const { return _filename; }
		const String& data() const { return _data; }
		usize pos() const { return _pos; }
		usize length() const { return _length; }
		usize line() const { return _line; }
		usize col() const { return _col; }
	};
}

#endif
