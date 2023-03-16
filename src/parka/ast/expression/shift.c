#include "parka/ast/expression/shift.h"
#include "parka/ast/expression/additive.h"
#include "parka/util/memory.h"

bool parseBitShiftExpression(Expression *out, Token *token)
{
	BitShiftExpression node = { 0 };

	if (!parseAdditiveExpression(&node.lhs, token))
		goto error;

	while (true)
	{
		bool shouldBreak = false;
		BitShiftType type;

		switch (token->type)
		{
			case TOKEN_LEFT_BIT_SHIFT:
				type = BIT_SHIFT_LEFT;
				break;

			case TOKEN_RIGHT_BIT_SHIFT:
				type = BIT_SHIFT_RIGHT;
				break;

			default:
				shouldBreak = true;
				break;
		}

		if (shouldBreak)
			break;
		
		incrementToken(token);

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

	bitShiftExpressionFree(&node);
	return false;
}

void bitShiftExpressionFree(BitShiftExpression *node)
{
	expressionFree(&node->lhs);

	for (usize i = 0; i < node->rhsCount; ++i)
		expressionFree(&node->rhs[i].expr);

	deallocate(node->rhs);
}
