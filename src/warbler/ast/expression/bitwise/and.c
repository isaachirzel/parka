#include <warbler/ast/expression/bitwise/and.h>

// local headers
#include <warbler/print.h>

// standard headers
#include <stdlib.h>
#include <assert.h>

void bitwise_and_expression_init(BitwiseAndExpression *self)
{
	assert(self);

	equality_expression_init(&self->lhs);
	self->rhs = NULL;
	self->rhs_count = 0;
}

void bitwise_and_expression_free(BitwiseAndExpression *self)
{
	if (!self)
		return;

	equality_expression_free(&self->lhs);
	
	for (size_t i = 0; i < self->rhs_count; ++i)
		equality_expression_free(self->rhs + i);

	free(self->rhs);
}

static inline EqualityExpression *equality_expression_push(BitwiseAndExpression *self)
{
	size_t new_size = (self->rhs_count + 1) * sizeof(EqualityExpression);
	EqualityExpression *tmp = realloc(self->rhs, new_size);

	if (!tmp)
		return NULL;

	self->rhs = tmp;
	EqualityExpression *back = self->rhs + self->rhs_count;
	++self->rhs_count;

	equality_expression_init(back);

	return back;
}

Error bitwise_and_expression_parse(BitwiseAndExpression *self, TokenIterator *iter)
{
	assert(self != NULL);
	assert(iter != NULL);

	bitwise_and_expression_init(self);

	Error error;

	if ((error = equality_expression_parse(&self->lhs, iter)))
		return error;

	while (iter->token->type == TOKEN_AMPERSAND)
	{
		++iter->token;
		EqualityExpression *back = equality_expression_push(self);

		if (!back)
			return ERROR_MEMORY;

		if ((error = equality_expression_parse(back, iter)))
			return error;
	}

	return ERROR_NONE;
}

void bitwise_and_expression_print_tree(BitwiseAndExpression *self, unsigned depth)
{
	assert(self != NULL);

	if (self->rhs_count > 0)
		depth += 1;

	equality_expression_print_tree(&self->lhs, depth);

	for (size_t i = 0; i < self->rhs_count; ++i)
	{
		print_branch(depth - 1);
		puts("&");

		equality_expression_print_tree(self->rhs + i, depth);
	}
}
