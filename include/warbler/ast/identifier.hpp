#ifndef WARBLER_AST_IDENTIFIER_HPP
#define WARBLER_AST_IDENTIFIER_HPP

// local headers
#include <warbler/token.hpp>
#include <warbler/util/result.hpp>
#include <warbler/util/primitive.hpp>
#include <warbler/semantics/context.hpp>

namespace warbler::ast
{
	class Identifier
	{
	private:

		Location _location;
		String _text;
		String _symbol;

	public:

		Identifier(const Location& location, String&& text);

		static Result<Identifier> parse(TokenIterator& iter);

		void validate(semantics::Context& context);
		void print_tree(u32 depth = 0) const;

		const String& text() const { return _text; }
		const String& symbol() const { return _symbol; }
		const Location& location() const { return _location; }
	};

}
#endif
