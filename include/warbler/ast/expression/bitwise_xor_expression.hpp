#ifndef WARBLER_AST_EXPRESSION_BITWISE_XOR_HPP
#define WARBLER_AST_EXPRESSION_BITWISE_XOR_HPP

// local headers
#include <warbler/ast/expression/bitwise_and_expression.hpp>

namespace warbler::ast
{
	class BitwiseXorExpression
	{
	private:

		BitwiseAndExpression _lhs;
		Array<BitwiseAndExpression> _rhs;

	public:

		BitwiseXorExpression(BitwiseAndExpression&& lhs, Array<BitwiseAndExpression>&& rhs);

		static Result<BitwiseXorExpression> parse(TokenIterator& iter);

		void print_tree(u32 depth = 0) const;
	};
}
#endif
