#include "warbler/ast/expression/bitwise_and.h"
#include "warbler/ast/expression/equality.h"
#include "warbler/ast/expression/expression.h"
#include "warbler/util/memory.h"

bool parseBitwiseAndExpression(Expression *out, Token *token)
{
	BitwiseAndExpression node = { 0 };

	if (!parseEqualityExpression(&node.lhs, token))
		goto error;

	while (token->type == TOKEN_AMPERSAND)
	{
		incrementToken(token);

		Expression expression;

		if (!parseEqualityExpression(&expression, token))
			goto error;

		resizeArray(node.rhs, ++node.rhsCount);
		node.rhs[node.rhsCount - 1] = expression;
	}

	if (!node.rhs)
	{
		*out = node.lhs;
		return true;
	}

	out->type = EXPRESSION_BITWISE_AND;
	out->bitwiseAnd = new(BitwiseAndExpression);
	*out->bitwiseAnd = node;

	return true;

error:

	bitwiseAndExpressionFree(&node);
	return false;
}

void bitwiseAndExpressionFree(BitwiseAndExpression *node)
{
	expressionFree(&node->lhs);

	for (usize i = 0; i < node->rhsCount; ++i)
		expressionFree(node-> rhs + i);

	deallocate(node->rhs);
}
