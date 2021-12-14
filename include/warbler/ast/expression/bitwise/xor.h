#ifndef WARBLER_AST_EXPRESSION_BITWISE_XOR_H
#define WARBLER_AST_EXPRESSION_BITWISE_XOR_H

// local headers
#include <warbler/ast/expression/bitwise/and.h>

typedef struct BitwiseXorExpression
{
	BitwiseAndExpression *conditions;
	size_t condition_count;
} BitwiseXorExpression;

#endif
