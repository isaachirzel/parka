#ifndef PARKA_AST_EXPRESSION_EQUALITY_H
#define PARKA_AST_EXPRESSION_EQUALITY_H

#include "parka/ast/expression/expression.h"

typedef enum EqualityType
{
	EQUALITY_EQUALS,
	EQUALITY_NOT_EQUALS
} EqualityType;

typedef struct EqualityRhs
{
	Expression expr;
	EqualityType type;
} EqualityRhs;

typedef struct EqualityExpression
{
	Expression lhs;
	EqualityRhs* rhs;
	usize rhsCount;
} EqualityExpression;

bool parseEqualityExpression(Expression *out, Token *token);
void equalityExpressionFree(EqualityExpression *node);

#endif
