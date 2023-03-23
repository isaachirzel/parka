#include "parka/ast/expression/shift.hpp"
#include "parka/ast/expression/additive.hpp"


Optional<Box<Expression>> BitShiftExpression::parse(Token& token)
{
	BitShiftExpression node = { 0 };

	if (!parseAdditiveExpression(&node.lhs, token))
		goto error;

	while (true)
	{
		bool shouldBreak = false;
		BitShiftType type;

		switch (token.type())
		{
			case TokenType::LeftBitShift:
				type = BIT_SHIFT_LEFT;
				break;

			case TokenType::RightBitShift:
				type = BIT_SHIFT_RIGHT;
				break;

			default:
				shouldBreak = true;
				break;
		}

		if (shouldBreak)
			break;
		
		token.increment();

		Expression expression;

		if (!parseAdditiveExpression(&expression, token))
			goto error;

		resizeArray(node.rhs, ++node.rhsCount);
		node.rhs[node.rhsCount - 1] = (BitShiftRhs)
		{
			.type = type,
			.expr = expression
		};
	}
	
	if (!node.rhs)
	{
		*out = node.lhs;
	}
	else
	{
		out->type = EXPRESSION_SHIFT;
		*makeNew(out->shift) = node;
	}

	return true;
	
error:

	return false;
}
