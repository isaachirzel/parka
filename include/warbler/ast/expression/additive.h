#ifndef WARBLER_AST_EXPRESSION_ADDITIVE_H
#define WARBLER_AST_EXPRESSION_ADDITIVE_H

#include "warbler/ast/expression/expression.h"

typedef enum AdditiveType
{
	ADDITIVE_ADD,
	ADDITIVE_SUBTRACT
} AdditiveType;

typedef struct AdditiveRhs
{
	Expression expr;
	AdditiveType type;
} AdditiveRhs;

typedef struct AdditiveExpression
{
	Expression lhs;
	AdditiveRhs *rhs;
	usize rhsCount;
} AdditiveExpression;

bool parseAdditiveExpression(Expression *out, Token *token);
bool validateAdditiveExpression(AdditiveExpression *node, LocalSymbolTable *localTable);
void additiveExpressionFree(AdditiveExpression *node);
bool additiveExpressionGetType(Type *out, AdditiveExpression *expression, const Type *expected);

#endif
