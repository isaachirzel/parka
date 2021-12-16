#ifndef WARBLER_AST_EXPRESSION_BITWISE_SHIFT_H
#define WARBLER_AST_EXPRESSION_BITWISE_SHIFT_H

#include <warbler/ast/expression/arithmetic/additive.h>

typedef enum ShiftType
{
	SHIFT_LEFT,
	SHIFT_RIGHT
} ShiftType;

typedef struct ShiftExpressionRight
{
	AdditiveExpression *expression;
	ShiftType type;
} ShiftExpressionRight;

typedef struct ShiftExpression
{
	AdditiveExpression *expression;
	ShiftExpressionRight *shifts;
	size_t shift_count;
} ShiftExpression;

#endif
