#include "parka/ast/expression/boolean_and.h"
#include "parka/ast/expression/bitwise_or.h"
#include "parka/ast/expression/expression.h"
#include "parka/util/memory.h"

bool parseBooleanAndExpression(Expression *out, Token *token)
{
	BooleanAndExpression node = { 0 };

	if (!parseBitwiseOrExpression(&node.lhs, token))
		goto error;

	while (token->type == TOKEN_BOOLEAN_AND)
	{
		incrementToken(token);

		Expression expression;

		if (!parseBitwiseOrExpression(&expression, token))
			goto error;

		resizeArray(node.rhs, ++node.rhsCount);
		node.rhs[node.rhsCount - 1] = expression;
	}

	if (!node.rhs)
	{
		*out = node.lhs;
		return true;
	}

	out->type = EXPRESSION_BOOLEAN_AND;
	out->booleanAnd = new(BooleanAndExpression);
	*out->booleanAnd = node;

	return true;
	
error:

	booleanAndExpressionFree(&node);
	return false;
}

void booleanAndExpressionFree(BooleanAndExpression *node)
{
	expressionFree(&node->lhs);

	for (usize i = 0; i < node->rhsCount; ++i)
		expressionFree(node-> rhs + i);

	deallocate(node->rhs);
}
