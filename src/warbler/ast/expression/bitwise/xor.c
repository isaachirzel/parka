#include <warbler/ast/expression/bitwise/xor.h>

// standard headers
#include <stdlib.h>
#include <assert.h>

void bitwise_xor_expression_init(BitwiseXorExpression *out)
{
	assert(out != NULL);

	bitwise_and_expression_init(&out->lhs);
	out->rhs = NULL;
	out->rhs_count = 0;
}

void bitwise_xor_expression_free(BitwiseXorExpression *out)
{
	assert(out != NULL);

	bitwise_and_expression_free(&out->lhs);
	
	for (size_t i = 0; i < out->rhs_count; ++i)
		bitwise_and_expression_free(out->rhs + i);

	free(out->rhs);
}

static inline BitwiseAndExpression *push_bitwise_and_expression(BitwiseXorExpression *out)
{
	size_t new_size = (out->rhs_count + 1) * sizeof(BitwiseAndExpression);
	BitwiseAndExpression *tmp = realloc(out->rhs, new_size);

	if (!tmp)
		return NULL;

	out->rhs = tmp;
	BitwiseAndExpression *back = out->rhs + out->rhs_count;
	++out->rhs_count;

	bitwise_and_expression_init(back);

	return back;
}

static inline Error try_bitwise_xor_expression_parse(BitwiseXorExpression *out, TokenIterator *iter)
{
	Error error;

	if ((error = bitwise_and_expression_parse(&out->lhs, iter)))
		return error;

	while (iter->token->type == TOKEN_CARROT)
	{
		++iter->token;
		BitwiseAndExpression *back = push_bitwise_and_expression(out);

		if (!back)
			return ERROR_MEMORY;

		if ((error = bitwise_and_expression_parse(back, iter)))
			return error;
	}

	return ERROR_NONE;
}

Error bitwise_xor_expression_parse(BitwiseXorExpression *out, TokenIterator *iter)
{
	assert(out != NULL);
	assert(iter != NULL);

	bitwise_xor_expression_init(out);

	Error error = try_bitwise_xor_expression_parse(out, iter);

	if (error)
		bitwise_xor_expression_free(out);

	return error;
}
