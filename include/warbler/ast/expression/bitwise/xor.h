#ifndef WARBLER_AST_EXPRESSION_BITWISE_XOR_H
#define WARBLER_AST_EXPRESSION_BITWISE_XOR_H

// local headers
#include <warbler/ast/expression/bitwise/and.h>

typedef struct BitwiseXorExpression
{
	BitwiseAndExpression lhs;
	BitwiseAndExpression *rhs;
	size_t rhs_count;
} BitwiseXorExpression;

void bitwise_xor_expression_init(BitwiseXorExpression *out);
void bitwise_xor_expression_free(BitwiseXorExpression *out);
Error bitwise_xor_expression_parse(BitwiseXorExpression *out, TokenIterator *iter);

#endif
