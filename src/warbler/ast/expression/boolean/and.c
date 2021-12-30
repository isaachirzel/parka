#include <warbler/ast/expression/boolean/and.h>

// local headers
#include <warbler/print.h>

// standard headers
#include <stdlib.h>
#include <assert.h>

void boolean_and_expression_init(BooleanAndExpression *self)
{
	assert(self != NULL);

	bitwise_or_expression_init(&self->lhs);
	self->rhs = NULL;
	self->rhs_count = 0;
}

void boolean_and_expression_free(BooleanAndExpression *self)
{
	assert(self != NULL);

	bitwise_or_expression_free(&self->lhs);
	
	for (size_t i = 0; i < self->rhs_count; ++i)
		bitwise_or_expression_free(self->rhs + i);

	free(self->rhs);
}

static inline BitwiseOrExpression *push_bitwise_or_expression(BooleanAndExpression *self)
{
	size_t new_size = (self->rhs_count + 1) * sizeof(BitwiseOrExpression);
	BitwiseOrExpression *tmp = realloc(self->rhs, new_size);

	if (!tmp)
		return NULL;

	self->rhs = tmp;
	BitwiseOrExpression *back = self->rhs + self->rhs_count;
	++self->rhs_count;

	bitwise_or_expression_init(back);

	return back;
}

static inline Error try_boolean_and_expression_parse(BooleanAndExpression *self, TokenIterator *iter)
{
	Error error;

	if ((error = bitwise_or_expression_parse(&self->lhs, iter)))
		return error;

	while (iter->token->type == TOKEN_AND)
	{
		++iter->token;
		BitwiseOrExpression *back = push_bitwise_or_expression(self);

		if (!back)
			return ERROR_MEMORY;

		if ((error = bitwise_or_expression_parse(back, iter)))
			return error;
	}

	return ERROR_NONE;
}

Error boolean_and_expression_parse(BooleanAndExpression *self, TokenIterator *iter)
{
	assert(self != NULL);
	assert(iter != NULL);

	boolean_and_expression_init(self);

	Error error = try_boolean_and_expression_parse(self, iter);

	if (error)
		boolean_and_expression_free(self);

	return error;
}

void boolean_and_expression_print_tree(BooleanAndExpression *self, unsigned depth)
{
	assert(self != NULL);

	if (self->rhs_count > 0)
		depth += 1;

	bitwise_or_expression_print_tree(&self->lhs, depth);

	for (size_t i = 0; i < self->rhs_count; ++i)
	{
		print_branch(depth - 1);
		puts("and");

		bitwise_or_expression_print_tree(self->rhs + i, depth);
	}
}
