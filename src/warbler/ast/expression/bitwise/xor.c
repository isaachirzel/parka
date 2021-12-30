#include <warbler/ast/expression/bitwise/xor.h>

// local headers
#include <warbler/print.h>

// standard headers
#include <stdlib.h>
#include <assert.h>

void bitwise_xor_expression_init(BitwiseXorExpression *self)
{
	assert(self != NULL);

	bitwise_and_expression_init(&self->lhs);
	self->rhs = NULL;
	self->rhs_count = 0;
}

void bitwise_xor_expression_free(BitwiseXorExpression *self)
{
	assert(self != NULL);

	bitwise_and_expression_free(&self->lhs);
	
	for (size_t i = 0; i < self->rhs_count; ++i)
		bitwise_and_expression_free(self->rhs + i);

	free(self->rhs);
}

static inline BitwiseAndExpression *push_bitwise_and_expression(BitwiseXorExpression *self)
{
	size_t new_size = (self->rhs_count + 1) * sizeof(BitwiseAndExpression);
	BitwiseAndExpression *tmp = realloc(self->rhs, new_size);

	if (!tmp)
		return NULL;

	self->rhs = tmp;
	BitwiseAndExpression *back = self->rhs + self->rhs_count;
	++self->rhs_count;

	bitwise_and_expression_init(back);

	return back;
}

static inline Error try_bitwise_xor_expression_parse(BitwiseXorExpression *self, TokenIterator *iter)
{
	Error error;

	if ((error = bitwise_and_expression_parse(&self->lhs, iter)))
		return error;

	while (iter->token->type == TOKEN_CARROT)
	{
		++iter->token;
		BitwiseAndExpression *back = push_bitwise_and_expression(self);

		if (!back)
			return ERROR_MEMORY;

		if ((error = bitwise_and_expression_parse(back, iter)))
			return error;
	}

	return ERROR_NONE;
}

Error bitwise_xor_expression_parse(BitwiseXorExpression *self, TokenIterator *iter)
{
	assert(self != NULL);
	assert(iter != NULL);

	bitwise_xor_expression_init(self);

	Error error = try_bitwise_xor_expression_parse(self, iter);

	if (error)
		bitwise_xor_expression_free(self);

	return error;
}

void bitwise_xor_expression_print_tree(BitwiseXorExpression *self, unsigned depth)
{
	assert(self != NULL);

	if (self->rhs_count > 0)
		depth += 1;

	bitwise_and_expression_print_tree(&self->lhs, depth);

	for (size_t i = 0; i < self->rhs_count; ++i)
	{
		print_branch(depth - 1);
		puts("^");

		bitwise_and_expression_print_tree(self->rhs + i, depth);
	}
}
