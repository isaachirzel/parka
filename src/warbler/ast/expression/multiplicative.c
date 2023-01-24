#include "warbler/ast/expression/multiplicative.h"
#include "warbler/ast/expression/prefix.h"
#include "warbler/util/memory.h"

bool parseMultiplicativeExpression(Expression *out, Token *token)
{
	MultiplicativeExpression node = { 0 };

	if (!parsePrefix(&node.lhs, token))
		goto error;

	while (true)
	{
		bool shouldBreak = false;

		MultiplicativeType type;
		switch (token->type)
		{
			case TOKEN_MODULUS:
				type = MULTIPLICATIVE_MODULUS;
				break;

			case TOKEN_ASTERISK:
				type = MULTIPLICATIVE_MULTIPLY;
				break;

			case TOKEN_SLASH:
				type = MULTIPLICATIVE_DIVIDE;
				break;

			default:
				shouldBreak = true;
				break;
		}

		if (shouldBreak)
			break;

		incrementToken(token);

		Expression expression;

		if (!parsePrefix(&expression, token))
			goto error;

		resizeArray(node.rhs, ++node.rhsCount);
		node.rhs[node.rhsCount - 1] = (MultiplicativeRhs)
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

	out->type = EXPRESSION_MULTIPLICATIVE;
	*makeNew(out->multiplicative) = node;

	return true;
	
error:

	multiplicativeExpressionFree(&node);
	return false;
}

bool validateMultiplicativeExpression(MultiplicativeExpression *node, LocalSymbolTable *localTable)
{
	bool success = true;

	if (!validateExpression(&node->lhs, localTable))
		success = false;

	for (usize i = 0; i < node->rhsCount; ++i)
	{
		if (!validateExpression(&node->rhs[i].expr, localTable))
			success = false;
	}

	return success;
}

void multiplicativeExpressionFree(MultiplicativeExpression *node)
{
	expressionFree(&node->lhs);

	for (usize i = 0; i < node->rhsCount; ++i)
		expressionFree(&node->rhs[i].expr);

	deallocate(node->rhs);
}
