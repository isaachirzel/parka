#ifndef PARKA_AST_EXPRESSION_ADDITIVE_H
#define PARKA_AST_EXPRESSION_ADDITIVE_H

#include "parka/ast/expression/expression.h"

typedef enum AdditiveType
{
	ADDITIVE_ADD,
	ADDITIVE_SUBTRACT
} AdditiveType;

typedef struct AdditiveExpression
{
	Expression lhs;
	Expression rhs;
	AdditiveType type;
} AdditiveExpression;

bool parseAdditiveExpression(Expression *out, Token *token);
bool validateAdditiveExpression(AdditiveExpression *node, LocalSymbolTable *localTable);
void additiveExpressionFree(AdditiveExpression *node);
bool additiveExpressionGetType(Type *out, AdditiveExpression *expression, const Type *expected);

#endif
