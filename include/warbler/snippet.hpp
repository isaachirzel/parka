#ifndef WARBLER_SNIPPET_HPP
#define WARBLER_SNIPPET_HPP

#include <warbler/file.hpp>
#include <warbler/token.hpp>

namespace warbler
{
	class Snippet
	{
	private:

		const File& _file;
		Array<String> _lines;
		usize _end_col;
		usize _line;
		usize _col;

	public:

		Snippet(const File& file, usize pos, usize length);
		Snippet(const Token& token);
		Snippet(const Token& first, const Token& last);

		const String& filename() const { return _file.filename(); }
		const Array<String>& lines() const { return _lines; }
		usize start_pos() const { return _col; }
		usize end_col() const { return _end_col; }
		usize line() const { return _line; }
		usize start_col() const { return _col; }
	};
}

#endif
