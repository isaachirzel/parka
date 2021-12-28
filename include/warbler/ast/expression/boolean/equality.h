#ifndef WARBLER_AST_EXPRESSION_BOOLEAN_EQUALITY_H
#define WARBLER_AST_EXPRESSION_BOOLEAN_EQUALITY_H

// local headers
#include <warbler/ast/expression/boolean/comparison.h>

typedef enum EqualityType
{
	EQUALITY_EQUALS,
	EQUALITY_NOT_EQUALS
} EqualityType;

typedef struct EqualityRhs
{
	ComparisonExpression expr;
	EqualityType type;
} EqualityRhs;

typedef struct EqualityExpression
{
	ComparisonExpression lhs;
	EqualityRhs *rhs;
	size_t rhs_count;
} EqualityExpression;

void equality_expression_init(EqualityExpression *out);
void equality_expression_free(EqualityExpression *out);
Error equality_expression_parse(EqualityExpression *out, TokenIterator *iter);

#endif
