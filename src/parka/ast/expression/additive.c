#include "parka/ast/expression/additive.h"
#include "parka/ast/expression/expression.h"
#include "parka/ast/expression/multiplicative.h"
#include "parka/ast/primitive.h"
#include "parka/ast/type.h"
#include "parka/symbol.h"
#include "parka/symbol_table.h"
#include "parka/token.h"
#include "parka/util/memory.h"
#include "parka/util/print.h"

bool parseAdditiveExpressionRhs(Expression *out, Expression *lhs, AdditiveType type, Token *token)
{
	*out = (Expression)
	{
		.type = EXPRESSION_ADDITIVE
	};

	*makeNew(out->additive) = (AdditiveExpression)
	{
		.lhs = *lhs,
		.type = type
	};

	if (!parseMultiplicativeExpression(&out->additive->rhs, token))
		return false;

	return true;
}

bool getAdditiveType(AdditiveType *out, Token *token)
{
	switch (token->type)
	{
		case TOKEN_PLUS:
			*out = ADDITIVE_ADD;
			break;

		case TOKEN_MINUS:
			*out = ADDITIVE_SUBTRACT;
			break;

		default:
			return false;
	}

	incrementToken(token);

	return true;
}

bool parseAdditiveExpression(Expression *out, Token *token)
{
	if (!parseMultiplicativeExpression(out, token))
		return false;
	
	AdditiveType additiveType;

	if (!getAdditiveType(&additiveType, token))
		return true;

	Expression lhs = *out;

	*out = (Expression)
	{
		.type = EXPRESSION_ADDITIVE
	};

	*makeNew(out->additive) = (AdditiveExpression)
	{
		.lhs = lhs,
		.type = additiveType
	};

	if (!parseMultiplicativeExpression(&out->additive->rhs, token))
		return false;

	Expression *parent = out;

	while (getAdditiveType(&additiveType, token))
	{
		Expression lhs = parent->additive->rhs;

		if (!parseAdditiveExpressionRhs(&parent->additive->rhs, &lhs, additiveType, token))
			return false;

		parent = &parent->additive->rhs;
	}

	return true;
}

bool validateAdditiveExpression(AdditiveExpression *node, LocalSymbolTable *localTable)
{
	bool success = true;

	if (!validateExpression(&node->lhs, localTable))
		success = false;

	if (!validateExpression(&node->rhs, localTable))
		success = false;

	return success;
}

void additiveExpressionFree(AdditiveExpression *node)
{
	expressionFree(&node->lhs);
	expressionFree(&node->rhs);
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
	Type leftType;

	if (!expressionGetType(&leftType, &expression->lhs, expected))
		return false;

	Type rightType;
	
	if (!expressionGetType(&rightType, &expression->rhs, expected))
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
