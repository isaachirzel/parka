#include <warbler/ast/expression/arithmetic/multiplicative.h>

// local includes
#include <warbler/print.h>

// standard headers
#include <stdlib.h>
#include <assert.h>

void multiplicative_expression_init(MultiplicativeExpression *expr)
{
	prefix_expression_init(&expr->lhs);
	
	expr->rhs = NULL;
	expr->rhs_count = 0;
}

void multiplicative_expression_free(MultiplicativeExpression *expr)
{
	prefix_expression_free(&expr->lhs);

	for (size_t i = 0; i < expr->rhs_count; ++i)
		prefix_expression_free(&expr->rhs[i].expr);

	free(expr->rhs);
}

static inline MultiplicativeRhs *multiplicative_expression_rhs_push(MultiplicativeExpression *expr, MultiplicativeType type)
{
	size_t new_size = (expr->rhs_count + 1) * sizeof(MultiplicativeRhs);
	MultiplicativeRhs *tmp = realloc(expr->rhs, new_size);

	if (!tmp)
		return NULL;

	expr->rhs = tmp;
	MultiplicativeRhs *back = expr->rhs + expr->rhs_count;
	++expr->rhs_count;

	prefix_expression_init(&back->expr);
	back->type = type;

	return back;
}

Error try_multiplicative_expression_parse(MultiplicativeExpression *out, TokenIterator *iter)
{
	Error error;

	if ((error = prefix_expression_parse(&out->lhs, iter)))
		return error;

	while (true)
	{
		bool should_break = false;
		MultiplicativeType type;

		switch (iter->token->type)
		{
			case TOKEN_MODULUS:
				type = MULTIPLICATIVE_MODULUS;
				break;

			case TOKEN_ASTERISK:
				type = MULTIPLICATIVE_MULTIPLY;
				break;

			case TOKEN_SLASH:
				type = MULTIPLICATIVE_DIVIDE;
				break;

			default:
				should_break = true;
				break;
		}

		if (should_break)
			break;

		MultiplicativeRhs *back = multiplicative_expression_rhs_push(out, type);

		if (!back)
			return ERROR_MEMORY;

		++iter->token;

		if ((error = prefix_expression_parse(&back->expr, iter)))
			return error;
	}

	return ERROR_NONE;
}

Error multiplicative_expression_parse(MultiplicativeExpression *out, TokenIterator *iter)
{
	assert(out != NULL);
	assert(iter != NULL);

	Error error = try_multiplicative_expression_parse(out, iter);

	if (error)
		multiplicative_expression_free(out);

	return error;
}

void multiplicative_expression_print(MultiplicativeExpression *self, unsigned depth)
{
	// prefix_expression_print(&self->lhs);
	print_tabs(depth);

	for (size_t i = 0; i < self->rhs_count; ++i)
	{
		switch (self->rhs[i].type)
		{
			case MULTIPLICATIVE_MULTIPLY:
				puts("*");
				break;

			case MULTIPLICATIVE_DIVIDE:
				puts("/");
				break;

			case MULTIPLICATIVE_MODULUS:
				puts("%");
				break;
		}
	}

}
