#ifndef WARBLER_AST_EXPRESSION_BITWISE_XOR_H
#define WARBLER_AST_EXPRESSION_BITWISE_XOR_H

#include "warbler/ast/expression/expression.h"

typedef struct BitwiseXorExpression
{
	Expression lhs;
	Expression* rhs;
	usize rhsCount;
} BitwiseXorExpression;

bool parseBitwiseXorExpression(Expression *out, Token *token);
void bitwiseXorExpressionFree(BitwiseXorExpression *node);

#endif
