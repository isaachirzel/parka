#include <warbler/ast/expression/boolean/comparison.h>

// standard headers
#include <stdlib.h>
#include <assert.h>

void comparison_expression_init(ComparisonExpression *out)
{
	assert(out != NULL);

	shift_expression_init(&out->lhs);
	out->rhs = NULL;
	out->rhs_count = 0;
}

void comparison_expression_free(ComparisonExpression *out)
{
	assert(out != NULL);

	shift_expression_free(&out->lhs);
	
	for (size_t i = 0; i < out->rhs_count; ++i)
		shift_expression_free(&out->rhs[i].expr);

	free(out->rhs);
}

static inline ComparisonRhs *push_comparison_rhs(ComparisonExpression *out, ComparisonType type)
{
	size_t new_size = (out->rhs_count + 1) * sizeof(ComparisonRhs);
	ComparisonRhs *tmp = realloc(out->rhs, new_size);

	if (!tmp)
		return NULL;

	out->rhs = tmp;
	ComparisonRhs *back = out->rhs + out->rhs_count;
	++out->rhs_count;

	shift_expression_init(&back->expr);
	back->type = type;

	return back;
}

static inline Error try_comparison_expression_parse(ComparisonExpression *out, TokenIterator *iter)
{
	Error error;

	if ((error = shift_expression_parse(&out->lhs, iter)))
		return error;

	while (true)
	{
		bool should_break = false;
		ComparisonType type;

		switch (iter->token->type)
		{
			case TOKEN_GREATER:
				type = COMPARISON_GREATER;
				break;

			case TOKEN_LESS:
				type = COMPARISON_LESS;
				break;

			case TOKEN_GREATER_EQUALS:
				type = COMPARISON_GREATER_EQUAL;
				break;

			case TOKEN_LESS_EQUALS:
				type = COMPARISON_LESS_EQUAL;
				break;

			default:
				should_break = true;
				break;
		}

		if (should_break)
			break;

		ComparisonRhs *back = push_comparison_rhs(out, type);

		if (!back)
			return ERROR_MEMORY;
		
		++iter->token;

		if ((error = shift_expression_parse(&back->expr, iter)))
			return error;
	}
	
	return ERROR_NONE;
}

Error comparison_expression_parse(ComparisonExpression *out, TokenIterator *iter)
{
	assert(out != NULL);
	assert(iter != NULL);

	comparison_expression_init(out);

	Error error = try_comparison_expression_parse(out, iter);

	if (error)
		comparison_expression_free(out);

	return error;
}
