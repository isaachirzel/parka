#include <warbler/ast/expression/conditional.h>

// local headers
#include <warbler/print.h>

// standard headers
#include <stdlib.h>

void conditional_expression_init(ConditionalExpression *self)
{
	assert(self != NULL);

	boolean_or_expression_init(&self->lhs);
	self->type = CONDITIONAL_NONE;
}

void conditional_expression_free(ConditionalExpression *self)
{
	assert(self != NULL);

	boolean_or_expression_free(&self->lhs);
}

static inline Error try_conditional_expression_parse(ConditionalExpression *self, TokenIterator *iter)
{
	Error error;

	if ((error = boolean_or_expression_parse(&self->lhs, iter)))
		return error;

	return ERROR_NONE;
}

Error conditional_expression_parse(ConditionalExpression *self, TokenIterator *iter)
{
	assert(self != NULL);
	assert(iter != NULL);

	conditional_expression_init(self);

	Error error = try_conditional_expression_parse(self, iter);

	if (error)
		conditional_expression_free(self);

	return error;
}

void conditional_expression_print_tree(ConditionalExpression *self, unsigned depth)
{
	boolean_or_expression_print_tree(&self->lhs, depth);

	if (self->type == CONDITIONAL_TERNARY)
	{
		debug("not implemented");
	}
}
