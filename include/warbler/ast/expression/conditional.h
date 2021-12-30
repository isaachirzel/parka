#ifndef WARBLER_AST_EXPRESSION_CONDITIONAL_H
#define WARBLER_AST_EXPRESSION_CONDITIONAL_H

// local headers
#include <warbler/ast/expression/boolean/or.h>

struct Expression;

typedef enum ConditionalType
{
	CONDITIONAL_NONE,
	CONDITIONAL_TERNARY
} ConditionalType;

typedef struct ConditionalExpression
{
	BooleanOrExpression lhs;
	ConditionalType type;
} ConditionalExpression;

void conditional_expression_init(ConditionalExpression *self);
void conditional_expression_free(ConditionalExpression *self);
Error conditional_expression_parse(ConditionalExpression *self, TokenIterator *iter);
void conditional_expression_print_tree(ConditionalExpression *self, unsigned depth);

#endif
