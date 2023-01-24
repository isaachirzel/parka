#include "warbler/ast/expression/bitwise_or.h"
#include "warbler/ast/expression/bitwise_xor.h"
#include "warbler/util/memory.h"

bool parseBitwiseOrExpression(Expression *out, Token *token)
{
	BitwiseOrExpression node = { 0 };

	if (!parseBitwiseXorExpression(&node.lhs, token))
		goto error;

	while (token->type == TOKEN_PIPE)
	{
		incrementToken(token);

		Expression expression;

		if (!parseBitwiseXorExpression(&expression, token))
			goto error;

		resizeArray(node.rhs, ++node.rhsCount);
		node.rhs[node.rhsCount - 1] = expression;
	}

	if (!node.rhs)
	{
		*out = node.lhs;
		return true;
	}

	out->type = EXPRESSION_BITWISE_OR;
	*makeNew(out->bitwiseOr) = node;

	return true;
	
error:

	bitwiseOrExpressionFree(&node);
	return false;
}

void bitwiseOrExpressionFree(BitwiseOrExpression *node)
{
	expressionFree(&node->lhs);

	for (usize i = 0; i < node->rhsCount; ++i)
		expressionFree(node-> rhs + i);

	deallocate(node->rhs);
}
