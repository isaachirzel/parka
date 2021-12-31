#include <warbler/ast/expression/boolean/equality.h>

// local headers
#include <warbler/print.h>

// standard headers
#include <stdlib.h>
#include <assert.h>

void equality_expression_init(EqualityExpression *self)
{
	comparison_expression_init(&self->lhs);
	
	self->rhs = NULL;
	self->rhs_count = 0;
}

void equality_expression_free(EqualityExpression *self)
{
	if (!self)
		return;

	comparison_expression_free(&self->lhs);
	
	for (size_t i = 0; i < self->rhs_count; ++i)
		comparison_expression_free(&self->rhs[i].expr);

	free(self->rhs);
}

static inline EqualityRhs *push_equality_rhs(EqualityExpression *self, EqualityType type)
{
	size_t new_size = (self->rhs_count + 1) * sizeof(EqualityRhs);
	EqualityRhs *tmp = realloc(self->rhs, new_size);

	if (!tmp)
		return NULL;

	self->rhs = tmp;
	EqualityRhs *back = self->rhs + self->rhs_count;
	++self->rhs_count;

	comparison_expression_init(&back->expr);
	back->type = type;

	return back;
}

Error equality_expression_parse(EqualityExpression *self, TokenIterator *iter)
{
	assert(self);
	assert(iter);

	equality_expression_init(self);

	Error error;

	if ((error = comparison_expression_parse(&self->lhs, iter)))
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

			case TOKEN_NOT_EQUALS:
				type = EQUALITY_NOT_EQUALS;
				break;

			default:
				should_break = true;
				break;
		}

		if (should_break)
			break;

		++iter->token;
		EqualityRhs *back = push_equality_rhs(self, type);

		if (!back)
			return ERROR_MEMORY;

		if ((error = comparison_expression_parse(&back->expr, iter)))
			return error;
	}

	return ERROR_NONE;
}

void equality_expression_print_tree(EqualityExpression *self, unsigned depth)
{
	assert(self != NULL);

	if (self->rhs_count > 0)
		depth += 1;

	comparison_expression_print_tree(&self->lhs, depth);

	for (size_t i = 0; i < self->rhs_count; ++i)
	{
		print_branch(depth - 1);

		if (self->rhs[i].type == EQUALITY_EQUALS)
			puts("==");
		else
			puts("!=");

		comparison_expression_print_tree(&self->rhs[i].expr, depth);
	}
}
