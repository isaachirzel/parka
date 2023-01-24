#ifndef WARBLER_AST_EXPRESSION_SHIFT_H
#define WARBLER_AST_EXPRESSION_SHIFT_H

#include "warbler/ast/expression/expression.h"

typedef enum BitShiftType
{
	BIT_SHIFT_LEFT,
	BIT_SHIFT_RIGHT
} BitShiftType;

typedef struct BitShiftRhs
{
	Expression expr;
	BitShiftType type;
} BitShiftRhs;

typedef struct BitShiftExpression
{
	Expression lhs;
	BitShiftRhs* rhs;
	usize rhsCount;
} BitShiftExpression;

bool parseBitShiftExpression(Expression *out, Token *token);
void bitShiftExpressionFree(BitShiftExpression *node);

#endif
