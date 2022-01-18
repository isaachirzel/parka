#ifndef WARBLER_AST_EXPRESSION_BITWISE_OR_HPP
#define WARBLER_AST_EXPRESSION_BITWISE_OR_HPP

// local headers
#include <warbler/ast/expression/bitwise_xor_expression.hpp>

namespace warbler
{
	class BitwiseOrExpression
	{
	private:

		BitwiseXorExpression _lhs;
		Array<BitwiseXorExpression> _rhs;	

	public:

		BitwiseOrExpression(BitwiseXorExpression&& lhs, Array<BitwiseXorExpression>&& rhs);

		static Result<BitwiseOrExpression> parse(TokenIterator& iter);

		void print_tree(u32 depth = 0) const;
	};
}

#endif
