#ifndef PARKA_AST_EXPRESSION_BOOLEAN_OR_H
#define PARKA_AST_EXPRESSION_BOOLEAN_OR_H

#include "parka/ast/expression/expression.h"

typedef struct BooleanOrExpression
{
	Expression lhs;
	Expression* rhs;
	usize rhsCount;
} BooleanOrExpression;

bool parseBooleanOrExpression(Expression *out, Token *token);
void booleanOrExpressionFree(BooleanOrExpression *node);

#endif
