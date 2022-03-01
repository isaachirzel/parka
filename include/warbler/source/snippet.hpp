#ifndef WARBLER_SOURCE_TEXT_HPP
#define WARBLER_SOURCE_TEXT_HPP

#include <warbler/source/file.hpp>
#include <warbler/lexicon/token.hpp>

namespace warbler::source
{
	class Snippet
	{
	private:

		const source::File& _file;
		Array<String> _lines;
		usize _end_pos;
		usize _line;
		usize _col;

	public:

		Snippet(const source::File& file, usize pos, usize length);
		Snippet(const lexicon::Token& token);
		Snippet(const lexicon::Token& first, const lexicon::Token& last);

		const String& filename() const { return _file.filename(); }
		const Array<String>& lines() const { return _lines; }
		usize start_pos() const { return _col; }
		usize end_pos() const { return _end_pos; }
		usize line() const { return _line; }
		usize col() const { return _col; }
	};
}

#endif
