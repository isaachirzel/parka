#ifndef WARBLER_AST_EXPRESSION_ARITHMETIC_ADDITIVE_HPP
#define WARBLER_AST_EXPRESSION_ARITHMETIC_ADDITIVE_HPP

#include <warbler/ast/expression/multiplicative_expression.hpp>

namespace warbler
{
typedef enum AdditiveType
{
	ADDITIVE_ADD,
	ADDITIVE_SUBTRACT
} AdditiveType;

typedef struct AdditiveRhs
{
	MultiplicativeExpression expr;
	AdditiveType type;
} AdditiveRhs;

typedef struct AdditiveExpression
{
	MultiplicativeExpression lhs;
	AdditiveRhs *rhs;
	size_t rhs_count;
} AdditiveExpression;

void additive_expression_init(AdditiveExpression *additive);
void additive_expression_free(AdditiveExpression *additive);
Error additive_expression_parse(AdditiveExpression *out, TokenIterator& iter);
void additive_expression_print_tree(AdditiveExpression *self, unsigned depth);
}

#endif
