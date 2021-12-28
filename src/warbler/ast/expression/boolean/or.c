#include <warbler/ast/expression/boolean/or.h>

// standard headers
#include <stdlib.h>
#include <assert.h>

void boolean_or_expression_init(BooleanOrExpression *out)
{
	assert(out != NULL);

	boolean_and_expression_init(&out->lhs);
	out->rhs = NULL;
	out->rhs_count = 0;
}

void boolean_or_expression_free(BooleanOrExpression *out)
{
	assert(out != NULL);

	boolean_and_expression_free(&out->lhs);
	
	for (size_t i = 0; i < out->rhs_count; ++i)
		boolean_and_expression_free(out->rhs + i);

	free(out->rhs);
}

static inline BooleanAndExpression *push_boolean_and_expression(BooleanOrExpression *out)
{
	size_t new_size = (out->rhs_count + 1) * sizeof(BooleanAndExpression);
	BooleanAndExpression *tmp = realloc(out->rhs, new_size);

	if (!tmp)
		return NULL;

	out->rhs = tmp;
	BooleanAndExpression *back = out->rhs + out->rhs_count;
	++out->rhs_count;

	boolean_and_expression_init(back);

	return back;
}

static inline Error try_boolean_or_expression_parse(BooleanOrExpression *out, TokenIterator *iter)
{
	Error error;

	if ((error = boolean_and_expression_parse(&out->lhs, iter)))
		return error;

	while (iter->token->type == TOKEN_OR)
	{
		++iter->token;
		BooleanAndExpression *back = push_boolean_and_expression(out);

		if (!back)
			return ERROR_MEMORY;

		if ((error = boolean_and_expression_parse(back, iter)))
			return error;
	}

	return ERROR_NONE;
}

Error boolean_or_expression_parse(BooleanOrExpression *out, TokenIterator *iter)
{
	assert(out != NULL);
	assert(iter != NULL);

	boolean_or_expression_init(out);

	Error error = try_boolean_or_expression_parse(out, iter);

	if (error)
		boolean_or_expression_free(out);

	return error;
}
