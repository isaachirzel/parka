#include <warbler/ast/expression/bitwise/and.h>

// standard headers
#include <stdlib.h>
#include <assert.h>

void bitwise_and_expression_init(BitwiseAndExpression *out)
{
	assert(out != NULL);

	equality_expression_init(&out->lhs);
	out->rhs = NULL;
	out->rhs_count = 0;
}

void bitwise_and_expression_free(BitwiseAndExpression *out)
{
	assert(out != NULL);

	equality_expression_free(&out->lhs);
	
	for (size_t i = 0; i < out->rhs_count; ++i)
		equality_expression_free(out->rhs + i);

	free(out->rhs);
}

static inline EqualityExpression *push_equality_expression(BitwiseAndExpression *out)
{
	size_t new_size = (out->rhs_count + 1) * sizeof(EqualityExpression);
	EqualityExpression *tmp = realloc(out->rhs, new_size);

	if (!tmp)
		return NULL;

	out->rhs = tmp;
	EqualityExpression *back = out->rhs + out->rhs_count;
	++out->rhs_count;

	equality_expression_init(back);

	return back;
}

static inline Error try_bitwise_and_expression_parse(BitwiseAndExpression *out, TokenIterator *iter)
{
	Error error;

	if ((error = equality_expression_parse(&out->lhs, iter)))
		return error;

	while (iter->token->type == TOKEN_AMPERSAND)
	{
		++iter->token;
		EqualityExpression *back = push_equality_expression(out);

		if (!back)
			return ERROR_MEMORY;

		if ((error = equality_expression_parse(back, iter)))
			return error;
	}

	return ERROR_NONE;
}

Error bitwise_and_expression_parse(BitwiseAndExpression *out, TokenIterator *iter)
{
	assert(out != NULL);
	assert(iter != NULL);

	bitwise_and_expression_init(out);

	Error error = try_bitwise_and_expression_parse(out, iter);

	if (error)
		bitwise_and_expression_free(out);

	return error;
}
