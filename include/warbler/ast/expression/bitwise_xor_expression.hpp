#ifndef WARBLER_AST_EXPRESSION_BITWISE_XOR_HPP
#define WARBLER_AST_EXPRESSION_BITWISE_XOR_HPP

// local headers
#include <warbler/ast/expression/bitwise_and_expression.hpp>
namespace warbler
{
typedef struct BitwiseXorExpression
{
	BitwiseAndExpression lhs;
	BitwiseAndExpression *rhs;
	size_t rhs_count;
} BitwiseXorExpression;

void bitwise_xor_expression_init(BitwiseXorExpression *self);
void bitwise_xor_expression_free(BitwiseXorExpression *self);
Error bitwise_xor_expression_parse(BitwiseXorExpression *self, TokenIterator& iter);
void bitwise_xor_expression_print_tree(BitwiseXorExpression *self, unsigned depth);
}
#endif
