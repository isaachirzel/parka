#ifndef WARBLER_AST_EXPRESSION_MULTIPLICATIVE_HPP
#define WARBLER_AST_EXPRESSION_MULTIPLICATIVE_HPP

// local headers
#include <warbler/ast/expression/primary_expression.hpp>

namespace warbler
{
	enum MultiplicativeType
	{
		MULTIPLICATIVE_MULTIPLY,
		MULTIPLICATIVE_DIVIDE,
		MULTIPLICATIVE_MODULUS
	};

	struct MultiplicativeRhs
	{
		PrimaryExpression expr;
		MultiplicativeType type;
	};

	class MultiplicativeExpression
	{
	private:

		PrimaryExpression _lhs;
		std::vector<MultiplicativeRhs> _rhs;
	
	public:

		MultiplicativeExpression(PrimaryExpression&& lhs, std::vector<MultiplicativeRhs>&& rhs);

		static Result<MultiplicativeExpression> parse(TokenIterator& iter);

		void print_tree(u32 depth = 0) const;
	};
}

#endif
