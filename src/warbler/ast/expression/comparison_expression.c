#include <warbler/ast/expression/comparison_expression.h>

// local headers
#include <warbler/print.h>

// standard headers
#include <stdlib.h>
#include <assert.h>

void comparison_expression_init(ComparisonExpression *self)
{
	assert(self);

	shift_expression_init(&self->lhs);
	self->rhs = NULL;
	self->rhs_count = 0;
}

void comparison_expression_free(ComparisonExpression *self)
{
	if (!self)
		return;

	shift_expression_free(&self->lhs);
	
	for (size_t i = 0; i < self->rhs_count; ++i)
		shift_expression_free(&self->rhs[i].expr);

	free(self->rhs);
}

static inline ComparisonRhs *push_comparison_rhs(ComparisonExpression *self, ComparisonType type)
{
	size_t new_size = (self->rhs_count + 1) * sizeof(ComparisonRhs);
	ComparisonRhs *tmp = realloc(self->rhs, new_size);

	if (!tmp)
		return NULL;

	self->rhs = tmp;
	ComparisonRhs *back = self->rhs + self->rhs_count;
	++self->rhs_count;

	shift_expression_init(&back->expr);
	back->type = type;

	return back;
}

Error comparison_expression_parse(ComparisonExpression *self, TokenIterator *iter)
{
	assert(self);
	assert(iter);

	comparison_expression_init(self);
	try(shift_expression_parse(&self->lhs, iter));

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

		ComparisonRhs *back = push_comparison_rhs(self, type);

		if (!back)
			return ERROR_MEMORY;
		
		++iter->token;

		try(shift_expression_parse(&back->expr, iter));
	}
	
	return ERROR_NONE;
}

void comparison_expression_print_tree(ComparisonExpression *self, unsigned depth)
{
	assert(self != NULL);

	if (self->rhs_count > 0)
		depth += 1;

	shift_expression_print_tree(&self->lhs, depth);

	for (size_t i = 0; i < self->rhs_count; ++i)
	{
		print_branch(depth - 1);

		switch (self->rhs[i].type)
		{
			case COMPARISON_GREATER:
				puts(">");
				break;

			case COMPARISON_LESS:
				puts("<");
				break;

			case COMPARISON_GREATER_EQUAL:
				puts(">=");
				break;

			case COMPARISON_LESS_EQUAL:
				puts("<=");
				break;

		}

		shift_expression_print_tree(&self->rhs[i].expr, depth);
	}
}
