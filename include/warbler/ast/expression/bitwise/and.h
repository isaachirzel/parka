#ifndef WARBLER_AST_EXPRESSION_BITWISE_AND_H
#define WARBLER_AST_EXPRESSION_BITWISE_AND_H

// local headers
#include <warbler/ast/expression/boolean/equality.h>

typedef struct BitwiseAndExpression
{
	EqualityExpression lhs;
	EqualityExpression *rhs;
	size_t rhs_count;
} BitwiseAndExpression;

void bitwise_and_expression_init(BitwiseAndExpression *out);
void bitwise_and_expression_free(BitwiseAndExpression *out);
Error bitwise_and_expression_parse(BitwiseAndExpression *out, TokenIterator *iter);

#endif
