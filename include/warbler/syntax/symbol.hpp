#ifndef WARBLER_SYNTAX_IDENTIFIER_HPP
#define WARBLER_SYNTAX_IDENTIFIER_HPP

// local headers
#include <warbler/lexicon/token.hpp>
#include <warbler/util/result.hpp>
#include <warbler/util/primitive.hpp>
#include <warbler/syntax//expression/primary_expression.hpp>

namespace warbler::syntax
{
	class Symbol : public Expression
	{
	private:

		Location _location;
		String _text;
		Type *_type;

	public:

		Symbol(const Location& location);

		static Result<Symbol> parse(TokenIterator& iter);

		bool validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx);
		void print_tree(u32 depth = 0) const;
		Type *get_type() { return _type; }

		const Location& location() const { return _location; }
		const String& text() const { return _text; }
	};

}
#endif
