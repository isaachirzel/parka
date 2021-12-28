#ifndef WARBLER_AST_EXPRESSION_BOOLEAN_COMPARISON_H
#define WARBLER_AST_EXPRESSION_BOOLEAN_COMPARISON_H

// local headers
#include <warbler/ast/expression/bitwise/shift.h>

typedef enum ComparisonType
{
	COMPARISON_GREATER,
	COMPARISON_LESS,
	COMPARISON_GREATER_EQUAL,
	COMPARISON_LESS_EQUAL
} ComparisonType;

typedef struct ComparisonRhs
{
	ShiftExpression expr;
	ComparisonType type;
} ComparisonRhs;

typedef struct ComparisonExpression
{
	ShiftExpression lhs;
	ComparisonRhs *rhs;
	size_t rhs_count;
} ComparisonExpression;

void comparison_expression_init(ComparisonExpression *out);
void comparison_expression_free(ComparisonExpression *out);
Error comparison_expression_parse(ComparisonExpression *out, TokenIterator *iter);

#endif