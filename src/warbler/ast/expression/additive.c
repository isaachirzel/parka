#include "warbler/ast/expression/additive.h"
#include "warbler/ast/expression/multiplicative.h"
#include "warbler/ast/primitive.h"
#include "warbler/ast/type.h"
#include "warbler/symbol.h"
#include "warbler/symbol_table.h"
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

bool additiveExpressionGetSignedIntegerType(Type *out, const Primitive *left, const Primitive *right, const Type *expected)
{
	switch (right->type)
	{
		case PRIMITIVE_SIGNED_INTEGER:
			// TODO: Actually check the bytes
			*out = (Type) { .type = SYMBOL_PRIMITIVE, .index = INDEX_I32 }; 
			return true;

		default:
			break;
	}
	
	return false;
}

bool additiveExpressionPrimitiveType(Type *out, const Primitive *left, const Primitive *right, const Type *expected)
{
	switch (left->type)
	{
		case PRIMITIVE_SIGNED_INTEGER:
			return additiveExpressionGetSignedIntegerType(out, left, right, expected);

		default:
			break;
	}

	return false;
}

bool additiveExpressionGetType(Type *out, AdditiveExpression *expression, const Type *expected)
{
	assert(expression->rhsCount == 1);

	// Find defined operation

	Type leftType;

	if (!expressionGetType(&leftType, &expression->lhs, expected))
		return false;

	Type rightType;
	
	if (!expressionGetType(&rightType, &expression->rhs->expr, expected))
		return false;


	if (leftType.type == SYMBOL_PRIMITIVE)
	{
		const Primitive *leftPrimitive = symbolTableGetPrimitive(leftType.index);
		
		if (rightType.type == SYMBOL_PRIMITIVE)
		{
			const Primitive *rightPrimitive = symbolTableGetPrimitive(rightType.index);

			if (additiveExpressionPrimitiveType(out, leftPrimitive, rightPrimitive, expected))
				return true;
		}
		else
		{
			exitWithError("Primitive + Complex is not implemented yet.");
		
		}

	}
	else
	{
		exitWithError("Addition for complex types is not implemented yet.");
	}
	
	printError("`%s` cannot be added to `%s`.", typeGetName(&rightType), typeGetName(&leftType));

	return false;
}
