#include <warbler/ast/expression/boolean/or.h>

// local headers
#include <warbler/print.h>

// standard headers
#include <stdlib.h>
#include <assert.h>

void boolean_or_expression_init(BooleanOrExpression *self)
{
	assert(self);

	boolean_and_expression_init(&self->lhs);
	self->rhs = NULL;
	self->rhs_count = 0;
}

void boolean_or_expression_free(BooleanOrExpression *self)
{
	if (!self)
		return;

	boolean_and_expression_free(&self->lhs);
	
	for (size_t i = 0; i < self->rhs_count; ++i)
		boolean_and_expression_free(self->rhs + i);

	free(self->rhs);
}

static inline BooleanAndExpression *push_boolean_and_expression(BooleanOrExpression *self)
{
	size_t new_size = (self->rhs_count + 1) * sizeof(BooleanAndExpression);
	BooleanAndExpression *tmp = realloc(self->rhs, new_size);

	if (!tmp)
		return NULL;

	self->rhs = tmp;
	BooleanAndExpression *back = self->rhs + self->rhs_count;
	++self->rhs_count;

	boolean_and_expression_init(back);

	return back;
}

Error boolean_or_expression_parse(BooleanOrExpression *self, TokenIterator *iter)
{
	assert(self);
	assert(iter);

	boolean_or_expression_init(self);
	try(boolean_and_expression_parse(&self->lhs, iter));

	while (iter->token->type == TOKEN_OR)
	{
		++iter->token;
		BooleanAndExpression *back = push_boolean_and_expression(self);

		if (!back)
			return ERROR_MEMORY;

		try(boolean_and_expression_parse(back, iter));
	}

	return ERROR_NONE;
}

void boolean_or_expression_print_tree(BooleanOrExpression *self, unsigned depth)
{
	assert(self != NULL);

	if (self->rhs_count > 0)
		depth += 1;

	boolean_and_expression_print_tree(&self->lhs, depth);

	for (size_t i = 0; i < self->rhs_count; ++i)
	{
		print_branch(depth - 1);
		puts("or");

		boolean_and_expression_print_tree(self->rhs + i, depth);
	}
}
