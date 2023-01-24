#ifndef WARBLER_AST_EXPRESSION_BITWISE_AND_H
#define WARBLER_AST_EXPRESSION_BITWISE_AND_H

#include "warbler/ast/expression/expression.h"

typedef struct BitwiseAndExpression
{
	Expression lhs;
	Expression* rhs;
	usize rhsCount;
} BitwiseAndExpression;

bool parseBitwiseAndExpression(Expression *out, Token *token);
void bitwiseAndExpressionFree(BitwiseAndExpression *node);

#endif
