#ifndef WARBLER_AST_NAME_HPP
#define WARBLER_AST_NAME_HPP

#include <warbler/token.hpp>
#include <warbler/util/result.hpp>
#include <warbler/util/string.hpp>

namespace warbler::ast
{
	class Name
	{
	private:

		String _text;
		Location _location;

		Name(String&& text, const Location& location);

	public:

		Name();

		static Result<Name> parse(TokenIterator& iter);

		void print_tree(u32 depth = 0) const;

		const String& text() const { return _text; }
		const Location& location() const { return _location; }
	};
}

#endif
