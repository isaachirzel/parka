#include "parka/ast/expression/bitwise_xor.h"
#include "parka/ast/expression/bitwise_and.h"
#include "parka/util/memory.h"

bool parseBitwiseXorExpression(Expression *out, Token *token)
{
	BitwiseXorExpression node = { 0 };

	if (!parseBitwiseAndExpression(&node.lhs, token))
		goto error;

	while (token->type == TOKEN_CARROT)
	{
		incrementToken(token);

		Expression expression;

		if (!parseBitwiseAndExpression(&expression, token))
			goto error;

		resizeArray(node.rhs, ++node.rhsCount);
		node.rhs[node.rhsCount - 1] = expression;
	}

	if (!node.rhs)
	{
		*out = node.lhs;
		return true;
	}

	out->type = EXPRESSION_BITWISE_XOR;
	*makeNew(out->bitwiseXor) = node;

	return true;
	
error:

	bitwiseXorExpressionFree(&node);
	return false;
}

void bitwiseXorExpressionFree(BitwiseXorExpression *node)
{
	expressionFree(&node->lhs);

	for (usize i = 0; i < node->rhsCount; ++i)
		expressionFree(node-> rhs + i);

	deallocate(node->rhs);
}
