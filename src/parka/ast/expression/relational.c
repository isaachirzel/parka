#include "parka/ast/expression/relational.h"
#include "parka/ast/expression/shift.h"
#include "parka/util/memory.h"

bool parseRelationalExpression(Expression *out, Token *token)
{
	RelationalExpression node = { 0 };

	if (!parseBitShiftExpression(&node.lhs, token))
		goto error;

	while (true)
	{
		bool shouldBreak = false;

		RelationalType type;
		switch (token->type)
		{
			case TOKEN_GREATER_THAN:
				type = RELATIONAL_GREATER_THAN;
				break;

			case TOKEN_LESS_THAN:
				type = RELATIONAL_LESS_THAN;
				break;

			case TOKEN_GREATER_THAN_OR_EQUAL_TO:
				type = RELATIONAL_GREATER_THAN_OR_EQUAL_TO;
				break;

			case TOKEN_LESS_THAN_OR_EQUAL_TO:
				type = RELATIONAL_LESS_THAN_OR_EQUAL_TO;
				break;

			default:
				shouldBreak = true;
				break;
		}

		if (shouldBreak)
			break;

		incrementToken(token);

		Expression expression;

		if (!parseBitShiftExpression(&expression, token))
			goto error;

		resizeArray(node.rhs, ++node.rhsCount);
		node.rhs[node.rhsCount - 1] = (RelationalRhs)
		{
			.expr = expression,
			.type = type
		};
	}

	if (!node.rhs)
	{
		*out = node.lhs;
	}
	else
	{
		out->type = EXPRESSION_RELATIONAL;
		out->relational = new(RelationalExpression);
		*out->relational = node;
	}

	return true;
	
error:

	relationalExpressionFree(&node);
	return false;
}

void relationalExpressionFree(RelationalExpression *node)
{
	expressionFree(&node->lhs);

	for (usize i = 0; i < node->rhsCount; ++i)
		expressionFree(&node->rhs[i].expr);

	deallocate(node->rhs);
}
