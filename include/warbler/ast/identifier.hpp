#ifndef WARBLER_AST_IDENTIFIER_HPP
#define WARBLER_AST_IDENTIFIER_HPP

// local headers
#include <warbler/token.hpp>
#include <warbler/util/result.hpp>
#include <warbler/util/primitive.hpp>
#include <warbler/ast/expression/primary_expression.hpp>>

namespace warbler::ast
{
	class Identifier : public Expression
	{
	private:

		Location _location;
		String _text;

	public:

		Identifier(const Location& location, String&& text);

		static Result<Identifier> parse(TokenIterator& iter);

		bool validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx);
		Type *get_type(semantics::ModuleContext& mod_ctx) const;
		const Location& location() const;
		void print_tree(u32 depth = 0) const;

		const String& text() const { return _text; }
		const Location& location() const { return _location; }
	};

}
#endif
