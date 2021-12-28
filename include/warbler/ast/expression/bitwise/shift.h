#ifndef WARBLER_AST_EXPRESSION_BITWISE_SHIFT_H
#define WARBLER_AST_EXPRESSION_BITWISE_SHIFT_H

// local headers
#include <warbler/ast/expression/arithmetic/additive.h>

typedef enum ShiftType
{
	SHIFT_LEFT,
	SHIFT_RIGHT
} ShiftType;

typedef struct ShiftRhs
{
	AdditiveExpression expr;
	ShiftType type;
} ShiftRhs;

typedef struct ShiftExpression
{
	AdditiveExpression lhs;
	ShiftRhs *rhs;
	size_t rhs_count;
} ShiftExpression;

void shift_expression_init(ShiftExpression *out);
void shift_expression_free(ShiftExpression *out);
Error shift_expression_parse(ShiftExpression *out, TokenIterator *iter);

#endif
