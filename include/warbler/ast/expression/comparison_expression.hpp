#ifndef WARBLER_AST_EXPRESSION_BOOLEAN_COMPARISON_HPP
#define WARBLER_AST_EXPRESSION_BOOLEAN_COMPARISON_HPP

// local headers
#include <warbler/ast/expression/shift_expression.hpp>
namespace warbler
{
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

void comparison_expression_init(ComparisonExpression *self);
void comparison_expression_free(ComparisonExpression *self);
Error comparison_expression_parse(ComparisonExpression *self, TokenIterator& iter);
void comparison_expression_print_tree(ComparisonExpression *self, unsigned depth);
}
#endif