#ifndef WARBLER_AST_EXPRESSION_MULTIPLICATIVE_HPP
#define WARBLER_AST_EXPRESSION_MULTIPLICATIVE_HPP

// local headers
#include <warbler/ast/expression/affix_expression.hpp>

namespace warbler::ast
{
	enum MultiplicativeType
	{
		MULTIPLICATIVE_MULTIPLY,
		MULTIPLICATIVE_DIVIDE,
		MULTIPLICATIVE_MODULUS
	};

	struct MultiplicativeRhs
	{
		AffixExpression expr;
		MultiplicativeType type;
	};

	class MultiplicativeExpression
	{
	private:

		AffixExpression _lhs;
		Array<MultiplicativeRhs> _rhs;
	
	public:

		MultiplicativeExpression(AffixExpression&& lhs, Array<MultiplicativeRhs>&& rhs);

		static Result<MultiplicativeExpression> parse(TokenIterator& iter);

		bool validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx);
		void print_tree(u32 depth = 0) const;
	};
}

#endif
