#ifndef WARBLER_AST_EXPRESSION_MULTIPLICATIVE_H
#define WARBLER_AST_EXPRESSION_MULTIPLICATIVE_H

// local headers
#include <warbler/ast/expression/primary_expression.h>

typedef enum MultiplicativeType
{
	MULTIPLICATIVE_MULTIPLY,
	MULTIPLICATIVE_DIVIDE,
	MULTIPLICATIVE_MODULUS
} MultiplicativeType;

typedef struct MultiplicativeRhs
{
	PrimaryExpression expr;
	MultiplicativeType type;
} MultiplicativeRhs;

typedef struct MultiplicativeExpression
{
	PrimaryExpression lhs;
	MultiplicativeRhs *rhs;
	size_t rhs_count;
} MultiplicativeExpression;

void multiplicative_expression_init(MultiplicativeExpression *expr);
void multiplicative_expression_free(MultiplicativeExpression *expr);
Error multiplicative_expression_parse(MultiplicativeExpression *out, TokenIterator *iter);
void multiplicative_expression_print_tree(MultiplicativeExpression *self, unsigned depth);

#endif
