#include <warbler/ast/expression/bitwise/or.h>

// standard headers
#include <stdlib.h>
#include <assert.h>

void bitwise_or_expression_init(BitwiseOrExpression *out)
{
	assert(out != NULL);

	bitwise_xor_expression_init(&out->lhs);
	out->rhs = NULL;
	out->rhs_count = 0;
}

void bitwise_or_expression_free(BitwiseOrExpression *out)
{
	assert(out != NULL);

	bitwise_xor_expression_free(&out->lhs);
	
	for (size_t i = 0; i < out->rhs_count; ++i)
		bitwise_xor_expression_free(out->rhs + i);

	free(out->rhs);
}

static inline BitwiseXorExpression *push_bitwise_xor_expression(BitwiseOrExpression *out)
{
	size_t new_size = (out->rhs_count + 1) * sizeof(BitwiseXorExpression);
	BitwiseXorExpression *tmp = realloc(out->rhs, new_size);

	if (!tmp)
		return NULL;

	out->rhs = tmp;
	BitwiseXorExpression *back = out->rhs + out->rhs_count;
	++out->rhs_count;

	bitwise_xor_expression_init(back);

	return back;
}

static inline Error try_bitwise_or_expression_parse(BitwiseOrExpression *out, TokenIterator *iter)
{
	Error error;

	if ((error = bitwise_xor_expression_parse(&out->lhs, iter)))
		return error;

	while (iter->token->type == TOKEN_PIPELINE
	)
	{
		++iter->token;
		BitwiseXorExpression *back = push_bitwise_xor_expression(out);

		if (!back)
			return ERROR_MEMORY;

		if ((error = bitwise_xor_expression_parse(back, iter)))
			return error;
	}

	return ERROR_NONE;
}

Error bitwise_or_expression_parse(BitwiseOrExpression *out, TokenIterator *iter)
{
	assert(out != NULL);
	assert(iter != NULL);

	bitwise_or_expression_init(out);

	Error error = try_bitwise_or_expression_parse(out, iter);

	if (error)
		bitwise_or_expression_free(out);

	return error;
}
