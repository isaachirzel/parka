#ifndef WARBLER_AST_EXPRESSION_BOOLEAN_OR_H
#define WARBLER_AST_EXPRESSION_BOOLEAN_OR_H

#include "warbler/ast/expression/expression.h"

typedef struct BooleanOrExpression
{
	Expression lhs;
	Expression* rhs;
	usize rhsCount;
} BooleanOrExpression;

bool parseBooleanOrExpression(Expression *out, Token *token);
void booleanOrExpressionFree(BooleanOrExpression *node);

#endif
