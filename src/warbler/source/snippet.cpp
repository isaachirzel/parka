#include <warbler/source/snippet.hpp>

#include <iostream>

namespace warbler::source
{
	Snippet::Snippet(const source::File& file, usize pos, usize length) :
	_file(file),
	_line(file.get_line(pos)),
	_col(file.get_col(pos))
	{
		assert(pos + length < file.src().size());

		usize start_of_line = pos - _col;
		usize end = pos + length;
		usize current_line = _line;

		for (; pos < end; ++pos)
		{
			char character = file[pos];

			if (character == '\n')
			{
				_lines.emplace_back(file.src().substr(start_of_line, pos - start_of_line));
				start_of_line = pos + 1;
				current_line += 1;
			}
		}

		_end_pos = end - start_of_line;

		while (true)
		{
			auto character = file[pos];

			if (character == '\0' || character == '\n')
				break;

			pos += 1;
		}

		_lines.emplace_back(file.src().substr(start_of_line, pos - start_of_line));
	}

	Snippet::Snippet(const lexicon::Token& token) :
	Snippet(token.file(), token.pos(), token.length())
	{}

	Snippet::Snippet(const lexicon::Token& first, const lexicon::Token& last) :
	Snippet(first.file(), first.pos(), last.pos() + last.length() - first.pos())
	{
		assert(&first.file() == &last.file());
		assert(first.pos() <= last.pos());
	}
}
