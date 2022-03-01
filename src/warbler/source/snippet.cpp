#include <warbler/source/snippet.hpp>

namespace warbler::source
{
	Snippet::Snippet(const source::File& file, usize pos, usize length) :
	_file(file),
	_line(file.get_line(pos)),
	_col(file.get_col(pos))
	{
		Array<String> lines;

		 
	}

	Snippet::Snippet(const lexicon::Token& token) :
	Snippet(token.file(), token.pos(), token.length())
	{}

	Snippet::Snippet(const lexicon::Token& first, const lexicon::Token& last) :
	_file(first.file())
	{
		assert(&first.file() == &last.file());


	}
}
