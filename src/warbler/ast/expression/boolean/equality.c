#include <warbler/ast/expression/boolean/equality.h>

// standard headers
#include <stdlib.h>
#include <assert.h>

void equality_expression_init(EqualityExpression *out)
{
	assert(out != NULL);

	comparison_expression_init(&out->lhs);
	out->rhs = NULL;
	out->rhs_count = 0;
}

void equality_expression_free(EqualityExpression *out)
{
	assert(out != NULL);

	comparison_expression_free(&out->lhs);
	
	for (size_t i = 0; i < out->rhs_count; ++i)
		comparison_expression_free(&out->rhs[i].expr);

	free(out->rhs);
}

static inline EqualityRhs *push_equality_rhs(EqualityExpression *out, EqualityType type)
{
	size_t new_size = (out->rhs_count + 1) * sizeof(EqualityRhs);
	EqualityRhs *tmp = realloc(out->rhs, new_size);

	if (!tmp)
		return NULL;

	out->rhs = tmp;
	EqualityRhs *back = out->rhs + out->rhs_count;
	++out->rhs_count;

	comparison_expression_init(&back->expr);
	back->type = type;

	return back;
}

static inline Error try_equality_expression_parse(EqualityExpression *out, TokenIterator *iter)
{
	Error error;

	if ((error = comparison_expression_parse(&out->lhs, iter)))
		return error;

	while (true)
	{
		bool should_break = false;
		EqualityType type;

		switch (iter->token->type)
		{
			case TOKEN_EQUALS:
				type = EQUALITY_EQUALS;
				break;

			case TOKEN_NEQUALS:
				type = EQUALITY_NOT_EQUALS;
				break;

			default:
				should_break = true;
				break;
		}

		if (should_break)
			break;

		++iter->token;
		EqualityRhs *back = push_equality_rhs(out, type);

		if (!back)
			return ERROR_MEMORY;

		if ((error = comparison_expression_parse(&back->expr, iter)))
			return error;
	}

	return ERROR_NONE;
}

Error equality_expression_parse(EqualityExpression *out, TokenIterator *iter)
{
	assert(out != NULL);
	assert(iter != NULL);

	equality_expression_init(out);

	Error error = try_equality_expression_parse(out, iter);

	if (error)
		equality_expression_free(out);

	return error;
}
