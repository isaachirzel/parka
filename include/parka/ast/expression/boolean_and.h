#ifndef PARKA_AST_EXPRESSION_BOOLEAN_AND_H
#define PARKA_AST_EXPRESSION_BOOLEAN_AND_H

#include "parka/ast/expression/expression.h"

typedef struct BooleanAndExpression
{
	Expression lhs;
	Expression* rhs;
	usize rhsCount;
} BooleanAndExpression;

bool parseBooleanAndExpression(Expression *out, Token *token);
void booleanAndExpressionFree(BooleanAndExpression *node);

#endif
