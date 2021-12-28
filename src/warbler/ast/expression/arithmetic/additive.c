#include <warbler/ast/expression/arithmetic/additive.h>

// local headers
#include <warbler/ast/expression/arithmetic/multiplicative.h>

// standard headers
#include <stdlib.h>
#include <assert.h>

void additive_expression_init(AdditiveExpression *additive)
{
	multiplicative_expression_init(&additive->lhs);

	additive->rhs = NULL;
	additive->rhs_count = 0;
}

void additive_expression_free(AdditiveExpression *additive)
{
	multiplicative_expression_free(&additive->lhs);

	for (size_t i = 0; i < additive->rhs_count; ++i)
		multiplicative_expression_free(&additive->rhs[i].expr);

	free(additive->rhs);
}

static inline AdditiveRhs *additive_expression_rhs_push(AdditiveExpression *expr, AdditiveType type)
{
	size_t new_size = (expr->rhs_count + 1) * sizeof(AdditiveRhs);
	AdditiveRhs *tmp = realloc(expr->rhs, new_size);

	if (!tmp)
		return NULL;

	expr->rhs = tmp;
	AdditiveRhs *back = expr->rhs + expr->rhs_count;
	++expr->rhs_count;

	multiplicative_expression_init(&back->expr);
	back->type = type;

	return back;
}

Error try_additive_expression_parse(AdditiveExpression *out, TokenIterator *iter)
{
	Error error;

	if ((error = multiplicative_expression_parse(&out->lhs, iter)))
		return error;

	while (iter->token->type == TOKEN_PLUS || iter->token->type == TOKEN_MINUS)
	{
		AdditiveType type = iter->token->type == TOKEN_PLUS
			? ADDITIVE_ADD
			: ADDITIVE_SUBTRACT;

		AdditiveRhs *back = additive_expression_rhs_push(out, type);

		if (!back)
			return ERROR_MEMORY;

		++iter->token;

		if ((error = multiplicative_expression_parse(&back->expr, iter)))
			return error;
	}

	return ERROR_NONE;
}

Error additive_expression_parse(AdditiveExpression *additive, TokenIterator *iter)
{
	assert(additive != NULL);
	assert(iter != NULL);

	additive_expression_init(additive);

	Error error = try_additive_expression_parse(additive, iter);

	if (error)
		additive_expression_free(additive);

	return error;
}

