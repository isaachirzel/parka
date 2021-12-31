#include <warbler/ast/expression/bitwise/shift.h>

// local headers
#include <warbler/print.h>

// standard headers
#include <stdlib.h>
#include <assert.h>

void shift_expression_init(ShiftExpression *self)
{
	assert(self);

	additive_expression_init(&self->lhs);
	self->rhs = NULL;
	self->rhs_count = 0;
}

void shift_expression_free(ShiftExpression *self)
{
	if (!self)
		return;

	additive_expression_free(&self->lhs);
	
	for (size_t i = 0; i < self->rhs_count; ++i)
		additive_expression_free(&self->rhs[i].expr);

	free(self->rhs);
}

static inline ShiftRhs *push_shift_rhs(ShiftExpression *self, ShiftType type)
{
	size_t new_size = (self->rhs_count + 1) * sizeof(ShiftRhs);
	ShiftRhs *tmp = realloc(self->rhs, new_size);

	if (!tmp)
		return NULL;

	self->rhs = tmp;
	ShiftRhs *back = self->rhs + self->rhs_count;
	++self->rhs_count;

	additive_expression_init(&back->expr);
	back->type = type;

	return back;
}

Error shift_expression_parse(ShiftExpression *self, TokenIterator *iter)
{
	assert(self != NULL);
	assert(iter != NULL);

	shift_expression_init(self);
	
	Error error;

	if ((error = additive_expression_parse(&self->lhs, iter)))
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

		ShiftRhs *back = push_shift_rhs(self, type);

		if (!back)
			return ERROR_MEMORY;
		
		++iter->token;

		if ((error = additive_expression_parse(&back->expr, iter)))
			return error;
	}
	
	return ERROR_NONE;
}

void shift_expression_print_tree(ShiftExpression *self, unsigned depth)
{
	assert(self != NULL);

	if (self->rhs_count > 0)
		depth += 1;

	additive_expression_print_tree(&self->lhs, depth);

	for (size_t i = 0; i < self->rhs_count; ++i)
	{
		print_branch(depth - 1);

		if (self->rhs[i].type == SHIFT_LEFT)
			puts("<<");
		else
			puts(">>");

		additive_expression_print_tree(&self->rhs[i].expr, depth);
	}
}
