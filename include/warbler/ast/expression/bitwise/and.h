#ifndef WARBLER_AST_EXPRESSION_BITWISE_AND_H
#define WARBLER_AST_EXPRESSION_BITWISE_AND_H

// local headers
#include <warbler/ast/expression/bitwise/or.h>

typedef struct BitwiseAndExpression
{
	BitwiseOrExpression *conditions;
	size_t condition_count;
} BitwiseAndExpression;

#endif
