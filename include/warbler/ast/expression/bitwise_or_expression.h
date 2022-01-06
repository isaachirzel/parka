#ifndef WARBLER_AST_EXPRESSION_BITWISE_OR_H
#define WARBLER_AST_EXPRESSION_BITWISE_OR_H

// local headers
#include <warbler/ast/expression/bitwise_xor_expression.h>

typedef struct BitwiseOrExpression
{
	BitwiseXorExpression lhs;
	BitwiseXorExpression *rhs;	
	size_t rhs_count;
} BitwiseOrExpression;

void bitwise_or_expression_init(BitwiseOrExpression *out);
void bitwise_or_expression_free(BitwiseOrExpression *out);
Error bitwise_or_expression_parse(BitwiseOrExpression *out, TokenIterator *iter);
void bitwise_or_expression_print_tree(BitwiseOrExpression *self, unsigned depth);

#endif
