#include <warbler/ast/expression/arithmetic/additive.h>

// local headers
#include <warbler/print.h>

// standard headers
#include <stdlib.h>
#include <assert.h>

void additive_expression_init(AdditiveExpression *self)
{
	multiplicative_expression_init(&self->lhs);

	self->rhs = NULL;
	self->rhs_count = 0;
}

void additive_expression_free(AdditiveExpression *self)
{
	multiplicative_expression_free(&self->lhs);

	for (size_t i = 0; i < self->rhs_count; ++i)
		multiplicative_expression_free(&self->rhs[i].expr);

	free(self->rhs);
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

Error try_additive_expression_parse(AdditiveExpression *self, TokenIterator *iter)
{
	Error error;

	if ((error = multiplicative_expression_parse(&self->lhs, iter)))
		return error;

	debugf("Is plus: %d\n", iter->token->type == TOKEN_PLUS);

	while (iter->token->type == TOKEN_PLUS || iter->token->type == TOKEN_MINUS)
	{
		AdditiveType type = iter->token->type == TOKEN_PLUS
			? ADDITIVE_ADD
			: ADDITIVE_SUBTRACT;

		AdditiveRhs *back = push_additive_rhs(self, type);

		if (!back)
			return ERROR_MEMORY;

		++iter->token;

		if ((error = multiplicative_expression_parse(&back->expr, iter)))
			return error;
	}

	return ERROR_NONE;
}

Error additive_expression_parse(AdditiveExpression *self, TokenIterator *iter)
{
	assert(self != NULL);
	assert(iter != NULL);

	additive_expression_init(self);

	Error error = try_additive_expression_parse(self, iter);

	if (error)
		additive_expression_free(self);

	return error;
}

void additive_expression_print_tree(AdditiveExpression *self, unsigned depth)
{
	assert(self != NULL);

	multiplicative_expression_print_tree(&self->lhs, depth + 1);
	
	for (size_t i = 0; i < self->rhs_count; ++i)
	{

		print_branch(depth);

		switch (self->rhs[i].type)
		{
			case ADDITIVE_ADD:
				puts("+");
				break;

			case ADDITIVE_SUBTRACT:
				puts("-");
				break;		
		}

		multiplicative_expression_print_tree(&self->rhs[i].expr, depth + 1);
	}
}
