#ifndef WARBLER_AST_EXPRESSION_BITWISE_SHIFT_HPP
#define WARBLER_AST_EXPRESSION_BITWISE_SHIFT_HPP

// local headers
#include <warbler/ast/expression/additive_expression.hpp>
namespace warbler
{
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

void shift_expression_init(ShiftExpression *self);
void shift_expression_free(ShiftExpression *self);
Error shift_expression_parse(ShiftExpression *self, TokenIterator& iter);
void shift_expression_print_tree(ShiftExpression *self, unsigned depth);
}
#endif
