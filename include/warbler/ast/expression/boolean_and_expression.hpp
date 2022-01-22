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

		void print_tree(u32 depth = 0) const;
	};
}

#endif
