#include <warbler/ast/expression/bitwise/or.h>

// local headers
#include <warbler/print.h>

// standard headers
#include <stdlib.h>
#include <assert.h>

void bitwise_or_expression_init(BitwiseOrExpression *self)
{
	assert(self != NULL);

	bitwise_xor_expression_init(&self->lhs);
	self->rhs = NULL;
	self->rhs_count = 0;
}

void bitwise_or_expression_free(BitwiseOrExpression *self)
{
	assert(self != NULL);

	bitwise_xor_expression_free(&self->lhs);
	
	for (size_t i = 0; i < self->rhs_count; ++i)
		bitwise_xor_expression_free(self->rhs + i);

	free(self->rhs);
}

static inline BitwiseXorExpression *push_bitwise_xor_expression(BitwiseOrExpression *self)
{
	size_t new_size = (self->rhs_count + 1) * sizeof(BitwiseXorExpression);
	BitwiseXorExpression *tmp = realloc(self->rhs, new_size);

	if (!tmp)
		return NULL;

	self->rhs = tmp;
	BitwiseXorExpression *back = self->rhs + self->rhs_count;
	++self->rhs_count;

	bitwise_xor_expression_init(back);

	return back;
}

static inline Error try_bitwise_or_expression_parse(BitwiseOrExpression *self, TokenIterator *iter)
{
	Error error;

	if ((error = bitwise_xor_expression_parse(&self->lhs, iter)))
		return error;

	while (iter->token->type == TOKEN_PIPELINE)
	{
		++iter->token;
		BitwiseXorExpression *back = push_bitwise_xor_expression(self);

		if (!back)
			return ERROR_MEMORY;

		if ((error = bitwise_xor_expression_parse(back, iter)))
			return error;
	}

	return ERROR_NONE;
}

Error bitwise_or_expression_parse(BitwiseOrExpression *self, TokenIterator *iter)
{
	assert(self != NULL);
	assert(iter != NULL);

	bitwise_or_expression_init(self);

	Error error = try_bitwise_or_expression_parse(self, iter);

	if (error)
		bitwise_or_expression_free(self);

	return error;
}

void bitwise_or_expression_print_tree(BitwiseOrExpression *self, unsigned depth)
{
	assert(self != NULL);

	if (self->rhs_count > 0)
		depth += 1;

	bitwise_xor_expression_print_tree(&self->lhs, depth);

	for (size_t i = 0; i < self->rhs_count; ++i)
	{
		print_branch(depth - 1);
		puts("|");

		bitwise_xor_expression_print_tree(self->rhs + i, depth);
	}
}
