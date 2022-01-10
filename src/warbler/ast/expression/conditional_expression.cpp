#include <warbler/ast/expression/conditional_expression.hpp>

// local headers
#include <warbler/print.hpp>

// standard headers
#include <cstdlib>

namespace warbler
{
void conditional_expression_init(ConditionalExpression *self)
{
	assert(self);

	boolean_or_expression_init(&self->lhs);
	self->type = CONDITIONAL_NONE;
}

void conditional_expression_free(ConditionalExpression *self)
{
	if (!self)
		return;

	boolean_or_expression_free(&self->lhs);
}

Error conditional_expression_parse(ConditionalExpression *self, TokenIterator& iter)
{
	assert(self != NULL);
	

	conditional_expression_init(self);
	try(boolean_or_expression_parse(&self->lhs, iter));

	return ERROR_NONE;
}

void conditional_expression_print_tree(ConditionalExpression *self, unsigned depth)
{
	boolean_or_expression_print_tree(&self->lhs, depth);

	if (self->type == CONDITIONAL_TERNARY)
	{
		debug("not implemented");
	}
}
}
