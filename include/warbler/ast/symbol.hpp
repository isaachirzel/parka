#ifndef WARBLER_AST_IDENTIFIER_HPP
#define WARBLER_AST_IDENTIFIER_HPP

// local headers
#include <warbler/token.hpp>
#include <warbler/util/result.hpp>
#include <warbler/util/primitive.hpp>
#include <warbler/ast/expression/primary_expression.hpp>

namespace warbler::ast
{
	class Symbol : public Expression
	{
	private:

		Location _location;
		String _text;
		Type *_type_name;

	public:

		Symbol(const Location& location);

		static Result<Symbol> parse(TokenIterator& iter);

		bool validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx);
		void print_tree(u32 depth = 0) const;
		Type *get_type(semantics::ModuleContext& mod_ctx) const { return _type_name; }

		const Location& location() const { return _location; }
		const String& text() const { return _text; }
	};

}
#endif
