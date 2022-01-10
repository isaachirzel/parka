#ifndef WARBLER_AST_EXPRESSION_BOOLEAN_AND_HPP
#define WARBLER_AST_EXPRESSION_BOOLEAN_AND_HPP

// local headers
#include <warbler/ast/expression/bitwise_or_expression.hpp>
namespace warbler
{
typedef struct BooleanAndExpression
{
	BitwiseOrExpression lhs;
	BitwiseOrExpression *rhs;
	size_t rhs_count;
} BooleanAndExpression;

void boolean_and_expression_init(BooleanAndExpression *out);
void boolean_and_expression_free(BooleanAndExpression *out);
Error boolean_and_expression_parse(BooleanAndExpression *out, TokenIterator& iter);
void boolean_and_expression_print_tree(BooleanAndExpression *self, unsigned depth);
}
#endif
