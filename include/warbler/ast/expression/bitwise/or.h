#ifndef WARBLER_AST_EXPRESSION_BITWISE_OR_H
#define WARBLER_AST_EXPRESSION_BITWISE_OR_H

// local headers
#include <warbler/ast/expression/bitwise/xor.h>

typedef struct BitwiseOrExpression
{
	BitwiseXorExpression *conditions;
	size_t condition_count;
} BitwiseOrExpression;

#endif
