#ifndef WARBLER_AST_EXPRESSION_BOOLEAN_OR_HPP
#define WARBLER_AST_EXPRESSION_BOOLEAN_OR_HPP

// local headers
#include <warbler/ast/expression/boolean_and_expression.hpp>
namespace warbler
{
typedef struct BooleanOrExpression
{
	BooleanAndExpression lhs;
	BooleanAndExpression *rhs;
	size_t rhs_count;
} BooleanOrExpression;

void boolean_or_expression_init(BooleanOrExpression *self);
void boolean_or_expression_free(BooleanOrExpression *self);
Error boolean_or_expression_parse(BooleanOrExpression *self, TokenIterator& iter);
void boolean_or_expression_print_tree(BooleanOrExpression *self, unsigned depth);
}
#endif
