#ifndef WARBLER_AST_EXPRESSION_BITWISE_OR_H
#define WARBLER_AST_EXPRESSION_BITWISE_OR_H

#include "warbler/ast/expression/expression.h"

typedef struct BitwiseOrExpression
{
	Expression lhs;
	Expression* rhs;
	usize rhsCount;
} BitwiseOrExpression;

bool parseBitwiseOrExpression(Expression *out, Token *token);
void bitwiseOrExpressionFree(BitwiseOrExpression *node);

#endif
