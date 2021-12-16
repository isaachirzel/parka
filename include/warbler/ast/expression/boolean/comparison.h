#ifndef WARBLER_AST_EXPRESSION_BOOLEAN_COMPARISON_H
#define WARBLER_AST_EXPRESSION_BOOLEAN_COMPARISON_H

// local headers
#include <warbler/ast/expression/bitwise/shift.h>

typedef struct ComparisonExpression
{
	ShiftExpression *conditions;
	size_t condition_count;
} ComparisonExpression;

#endif