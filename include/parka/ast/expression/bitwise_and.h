#ifndef PARKA_AST_EXPRESSION_BITWISE_AND_H
#define PARKA_AST_EXPRESSION_BITWISE_AND_H

#include "parka/ast/expression/expression.h"

typedef struct BitwiseAndExpression
{
	Expression lhs;
	Expression* rhs;
	usize rhsCount;
} BitwiseAndExpression;

bool parseBitwiseAndExpression(Expression *out, Token *token);
void bitwiseAndExpressionFree(BitwiseAndExpression *node);

#endif
