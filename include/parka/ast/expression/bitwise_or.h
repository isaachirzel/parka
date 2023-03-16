#ifndef PARKA_AST_EXPRESSION_BITWISE_OR_H
#define PARKA_AST_EXPRESSION_BITWISE_OR_H

#include "parka/ast/expression/expression.h"

typedef struct BitwiseOrExpression
{
	Expression lhs;
	Expression* rhs;
	usize rhsCount;
} BitwiseOrExpression;

bool parseBitwiseOrExpression(Expression *out, Token *token);
void bitwiseOrExpressionFree(BitwiseOrExpression *node);

#endif
