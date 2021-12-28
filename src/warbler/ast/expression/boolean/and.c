#include <warbler/ast/expression/boolean/and.h>

// standard headers
#include <stdlib.h>
#include <assert.h>

void boolean_and_expression_init(BooleanAndExpression *out)
{
	assert(out != NULL);

	bitwise_or_expression_init(&out->lhs);
	out->rhs = NULL;
	out->rhs_count = 0;
}

void boolean_and_expression_free(BooleanAndExpression *out)
{
	assert(out != NULL);

	bitwise_or_expression_free(&out->lhs);
	
	for (size_t i = 0; i < out->rhs_count; ++i)
		bitwise_or_expression_free(out->rhs + i);

	free(out->rhs);
}

static inline BitwiseOrExpression *push_bitwise_or_expression(BooleanAndExpression *out)
{
	size_t new_size = (out->rhs_count + 1) * sizeof(BitwiseOrExpression);
	BitwiseOrExpression *tmp = realloc(out->rhs, new_size);

	if (!tmp)
		return NULL;

	out->rhs = tmp;
	BitwiseOrExpression *back = out->rhs + out->rhs_count;
	++out->rhs_count;

	bitwise_or_expression_init(back);

	return back;
}

static inline Error try_boolean_and_expression_parse(BooleanAndExpression *out, TokenIterator *iter)
{
	Error error;

	if ((error = bitwise_or_expression_parse(&out->lhs, iter)))
		return error;

	while (iter->token->type == TOKEN_AND)
	{
		++iter->token;
		BitwiseOrExpression *back = push_bitwise_or_expression(out);

		if (!back)
			return ERROR_MEMORY;

		if ((error = bitwise_or_expression_parse(back, iter)))
			return error;
	}

	return ERROR_NONE;
}

Error boolean_and_expression_parse(BooleanAndExpression *out, TokenIterator *iter)
{
	assert(out != NULL);
	assert(iter != NULL);

	boolean_and_expression_init(out);

	Error error = try_boolean_and_expression_parse(out, iter);

	if (error)
		boolean_and_expression_free(out);

	return error;
}
