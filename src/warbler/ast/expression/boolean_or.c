#include "warbler/ast/expression/boolean_or.h"
#include "warbler/ast/expression/boolean_and.h"
#include "warbler/util/memory.h"

bool parseBooleanOrExpression(Expression *out, Token *token)
{
	BooleanOrExpression node = { 0 };

	if (!parseBooleanAndExpression(&node.lhs, token))
		goto error;

	while (token->type == TOKEN_BOOLEAN_OR)
	{
		incrementToken(token);

		Expression expression;

		if (!parseBooleanAndExpression(&expression, token))
			goto error;

		resizeArray(node.rhs, ++node.rhsCount);
		node.rhs[node.rhsCount - 1] = expression;
	}

	if (!node.rhs)
	{
		*out = node.lhs;
		return true;
	}

	out->type = EXPRESSION_BOOLEAN_OR;
	*makeNew(out->booleanOr) = node;

	return true;
	
error:

	booleanOrExpressionFree(&node);
	return false;
}

void booleanOrExpressionFree(BooleanOrExpression *node)
{
	expressionFree(&node->lhs);

	for (usize i = 0; i < node->rhsCount; ++i)
		expressionFree(node-> rhs + i);

	deallocate(node->rhs);
}
