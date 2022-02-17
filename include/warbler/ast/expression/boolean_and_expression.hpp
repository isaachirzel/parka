#ifndef WARBLER_AST_EXPRESSION_BOOLEAN_AND_HPP
#define WARBLER_AST_EXPRESSION_BOOLEAN_AND_HPP

// local headers
#include <warbler/ast/expression/bitwise_or_expression.hpp>

namespace warbler::ast
{
	class BooleanAndExpression
	{
	private:

		BitwiseOrExpression _lhs;
		Array<BitwiseOrExpression> _rhs;

	public:

		BooleanAndExpression(BitwiseOrExpression&& lhs, Array<BitwiseOrExpression>&& rhs);

		static Result<BooleanAndExpression> parse(TokenIterator& iter);

		bool validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx);
		Type *get_type(semantics::ModuleContext& mod_ctx) const;
		const Location& location() const;
		void print_tree(u32 depth = 0) const;
	};
}

#endif
