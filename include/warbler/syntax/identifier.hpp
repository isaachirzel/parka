#ifndef WARBLER_SYNTAX_NAME_HPP
#define WARBLER_SYNTAX_NAME_HPP

#include <warbler/lexicon/token.hpp>
#include <warbler/util/result.hpp>
#include <warbler/util/string.hpp>

namespace warbler::syntax
{
	class Identifier
	{
	private:

		Location _location;
		String _text;

		Identifier(const Location& location);

	public:

		Identifier(String&& text);
		Identifier();

		static Result<Identifier> parse(TokenIterator& iter);

		void print_tree(u32 depth = 0) const;

		const String& text() const { return _text; }
		const Location& location() const { return _location; }
	};
}

#endif
