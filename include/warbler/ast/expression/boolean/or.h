#ifndef WARBLER_AST_EXPRESSION_LOGICAL_OR_H
#define WARBLER_AST_EXPRESSION_LOGICAL_OR_H

// local headers
#include <warbler/ast/expression/boolean/and.h>

typedef struct BooleanOrExpression
{
	BooleanAndExpression *conditions;
	size_t condition_count;
} BooleanOrExpression;

#endif
