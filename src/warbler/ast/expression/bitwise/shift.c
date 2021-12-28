#include <warbler/ast/expression/bitwise/shift.h>

// standard headers
#include <stdlib.h>
#include <assert.h>

void shift_expression_init(ShiftExpression *out)
{
	assert(out != NULL);

	additive_expression_init(&out->lhs);
	out->rhs = NULL;
	out->rhs_count = 0;
}

void shift_expression_free(ShiftExpression *out)
{
	assert(out != NULL);

	additive_expression_free(&out->lhs);
	
	for (size_t i = 0; i < out->rhs_count; ++i)
		additive_expression_free(&out->rhs[i].expr);

	free(out->rhs);
}

static inline ShiftRhs *push_shift_rhs(ShiftExpression *out, ShiftType type)
{
	size_t new_size = (out->rhs_count + 1) * sizeof(ShiftRhs);
	ShiftRhs *tmp = realloc(out->rhs, new_size);

	if (!tmp)
		return NULL;

	out->rhs = tmp;
	ShiftRhs *back = out->rhs + out->rhs_count;
	++out->rhs_count;

	additive_expression_init(&back->expr);
	back->type = type;

	return back;
}

static inline Error try_shift_expression_parse(ShiftExpression *out, TokenIterator *iter)
{
	Error error;

	if ((error = additive_expression_parse(&out->lhs, iter)))
		return error;

	while (true)
	{
		bool should_break = false;
		ShiftType type;

		switch (iter->token->type)
		{
			case TOKEN_LSHIFT:
				type = SHIFT_LEFT;
				break;

			case TOKEN_RSHIFT:
				type = SHIFT_RIGHT;
				break;

			default:
				should_break = true;
				break;
		}

		if (should_break)
			break;

		ShiftRhs *back = push_shift_rhs(out, type);

		if (!back)
			return ERROR_MEMORY;
		
		++iter->token;

		if ((error = additive_expression_parse(&back->expr, iter)))
			return error;
	}
	
	return ERROR_NONE;
}

Error shift_expression_parse(ShiftExpression *out, TokenIterator *iter)
{
	assert(out != NULL);
	assert(iter != NULL);

	shift_expression_init(out);

	Error error = try_shift_expression_parse(out, iter);

	if (error)
		shift_expression_free(out);

	return error;
}
