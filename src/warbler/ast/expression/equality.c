#include "warbler/ast/expression/equality.h"
#include "warbler/ast/expression/relational.h"
#include "warbler/util/memory.h"

bool parseEqualityExpression(Expression *out, Token *token)
{
	EqualityExpression node = { 0 };

	if (!parseRelationalExpression(&node.lhs, token))
		goto error;

	while (true)
	{
		bool shouldBreak = false;

		EqualityType type;
		switch (token->type)
		{
			case TOKEN_EQUALS:
				type = EQUALITY_EQUALS;
				break;

			case TOKEN_NOT_EQUALS:
				type = EQUALITY_NOT_EQUALS;
				break;

			default:
				shouldBreak = true;
				break;
		}

		if (shouldBreak)
			break;

		incrementToken(token);

		Expression expression;

		if (!parseRelationalExpression(&expression, token))
			goto error;

		resizeArray(node.rhs, ++node.rhsCount);
		node.rhs[node.rhsCount - 1] = (EqualityRhs)
		{
			.type = type,
			.expr = expression
		};
	}

	if (!node.rhs)
	{
		*out = node.lhs;
		return true;
	}

	out->type = EXPRESSION_EQUALITY;
	*makeNew(out->equality) = node;

	return true;
	
error:

	equalityExpressionFree(&node);
	return false;
}

void equalityExpressionFree(EqualityExpression *node)
{
	expressionFree(&node->lhs);

	for (usize i = 0; i < node->rhsCount; ++i)
		expressionFree(&node->rhs[i].expr);

	deallocate(node->rhs);
}
