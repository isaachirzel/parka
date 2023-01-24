#include "warbler/ast/expression/additive.h"
#include "warbler/ast/expression/multiplicative.h"
#include "warbler/ast/type.h"
#include "warbler/util/memory.h"
#include "warbler/util/print.h"

bool parseAdditiveExpression(Expression *out, Token *token)
{
	AdditiveExpression node = { 0 };

	if (!parseMultiplicativeExpression(&node.lhs, token))
		return false;

	while (true)
	{
		AdditiveType type;

		if (token->type == TOKEN_PLUS)
		{
			type = ADDITIVE_ADD;
		}
		else if (token->type == TOKEN_MINUS)
		{
			type = ADDITIVE_ADD;
		}
		else
		{
			break;
		}

		incrementToken(token);

		Expression expression;

		if (!parseMultiplicativeExpression(&expression, token))
			goto error;

		resizeArray(node.rhs, ++node.rhsCount);

		node.rhs[node.rhsCount - 1] = (AdditiveRhs)
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

	out->additive = allocate(sizeof(*out->additive));
	out->type = EXPRESSION_ADDITIVE;
	*out->additive = node;
	
	return true;

error:

	additiveExpressionFree(&node);

	return false;
}

bool validateAdditiveExpression(AdditiveExpression *node, LocalSymbolTable *localTable)
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

void additiveExpressionFree(AdditiveExpression *node)
{
	expressionFree(&node->lhs);

	for (usize i = 0; i < node->rhsCount; ++i)
		expressionFree(&node->rhs[i].expr);

	deallocate(node->rhs);
}

bool additiveExpressionGetType(Type *out, AdditiveExpression *expression, const Type *expected)
{
	// TODO: Remove debug asserts
	assert(expression->rhsCount == 1);

	Type leftType;

	if (!expressionGetType(&leftType, &expression->lhs, expected))
		return false;

	Type rightType;
	
	if (!expressionGetType(&rightType, &expression->rhs->expr, expected))
		return false;

	exitNotImplemented();
}
