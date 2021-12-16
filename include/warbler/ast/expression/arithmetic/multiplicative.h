#ifndef WARBLER_AST_EXPRESSION_MULTIPLICATIVE_H
#define WARBLER_AST_EXPRESSION_MULTIPLICATIVE_H

// local headers
#include <warbler/ast/constant.h>

typedef enum MultiplicativeType
{
	MULTIPLICATIVE_MULTIPLY,
	MULTIPLICATIVE_DIVIDE,
	MULTIPLICATIVE_MODULUS,
} MultiplicativeType;

typedef struct MultiplicativeRhs
{
	Constant *constant;
	MultiplicativeType type;
} MultiplicativeRhs;

typedef struct MultiplicativeExpression
{
	Constant *lhs;
	MultiplicativeRhs *rhs;
	size_t rhs_count;
} MultiplicativeExpression;

void multiplicative_expression_init(MultiplicativeExpression *expr);
void multiplicative_expression_free(MultiplicativeExpression *expr);
void multiplicative_rhs_init(MultiplicativeRhs *rhs);
void multiplicative_rhs_free(MultiplicativeRhs *rhs);
Error multiplicative_expression_parse(MultiplicativeExpression *out, TokenIterator *iter);

#endif
