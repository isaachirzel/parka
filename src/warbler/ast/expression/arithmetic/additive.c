#include <warbler/ast/expression/arithmetic/additive.h>

// local headers
#include <warbler/print.h>

// standard headers
#include <stdlib.h>
#include <assert.h>

void additive_expression_init(AdditiveExpression *out)
{
	multiplicative_expression_init(&out->lhs);

	out->rhs = NULL;
	out->rhs_count = 0;
}

void additive_expression_free(AdditiveExpression *out)
{
	multiplicative_expression_free(&out->lhs);

	for (size_t i = 0; i < out->rhs_count; ++i)
		multiplicative_expression_free(&out->rhs[i].expr);

	free(out->rhs);
}

static inline AdditiveRhs *push_additive_rhs(AdditiveExpression *expr, AdditiveType type)
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

		AdditiveRhs *back = push_additive_rhs(out, type);

		if (!back)
			return ERROR_MEMORY;

		++iter->token;

		if ((error = multiplicative_expression_parse(&back->expr, iter)))
			return error;
	}

	return ERROR_NONE;
}

Error additive_expression_parse(AdditiveExpression *out, TokenIterator *iter)
{
	assert(out != NULL);
	assert(iter != NULL);

	additive_expression_init(out);

	Error error = try_additive_expression_parse(out, iter);

	if (error)
		additive_expression_free(out);

	return error;
}

void additive_expression_print(AdditiveExpression *self, unsigned depth)
{
	assert(self != NULL);
	
	//multiplicative_expression_print(&self->lhs, depth);
	print_tabs(depth);
	puts("MULT");
	
	for (size_t i = 0; i < self->rhs_count; ++i)
	{
		print_tabs(depth + 1);

		switch (self->rhs[i].type)
		{
			case ADDITIVE_ADD:
				puts("+");
				break;

			case ADDITIVE_SUBTRACT:
				puts("-");
				break;		
		}

		print_tabs(depth + 1);
		puts("MULT");
	}
}
