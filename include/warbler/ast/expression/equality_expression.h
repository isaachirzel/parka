#ifndef WARBLER_AST_EXPRESSION_BOOLEAN_EQUALITY_H
#define WARBLER_AST_EXPRESSION_BOOLEAN_EQUALITY_H

// local headers
#include <warbler/ast/expression/comparison_expression.h>

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

void equality_expression_init(EqualityExpression *self);
void equality_expression_free(EqualityExpression *self);
Error equality_expression_parse(EqualityExpression *self, TokenIterator *iter);
void equality_expression_print_tree(EqualityExpression *self, unsigned depth);

#endif
