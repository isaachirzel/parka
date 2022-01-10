#include <warbler/ast/expression/additive_expression.hpp>

// local headers
#include <warbler/print.hpp>

// standard headers
#include <cstdlib>
#include <cassert>
namespace warbler
{
void additive_expression_init(AdditiveExpression *self)
{
	assert(self);

	multiplicative_expression_init(&self->lhs);

	self->rhs = NULL;
	self->rhs_count = 0;
}

void additive_expression_free(AdditiveExpression *self)
{
	if (!self)
		return;

	multiplicative_expression_free(&self->lhs);

	for (size_t i = 0; i < self->rhs_count; ++i)
		multiplicative_expression_free(&self->rhs[i].expr);

	free(self->rhs);
}

static inline AdditiveRhs *additive_expression_push(AdditiveExpression *self)
{
	size_t new_size = (self->rhs_count + 1) * sizeof(AdditiveRhs);
	AdditiveRhs *tmp = (AdditiveRhs*)realloc(self->rhs, new_size);

	if (!tmp)
		return NULL;

	AdditiveRhs *back = tmp + self->rhs_count;

	self->rhs = tmp;
	++self->rhs_count;

	return back;
}

Error additive_expression_parse(AdditiveExpression *self, TokenIterator& iter)
{
	assert(self != NULL);
	

	additive_expression_init(self);
	try(multiplicative_expression_parse(&self->lhs, iter));

	while (iter->type == TOKEN_PLUS || iter->type == TOKEN_MINUS)
	{
		AdditiveRhs *back = additive_expression_push(self);

		if (!back)
			return ERROR_MEMORY;

		back->type = iter->type == TOKEN_PLUS
			? ADDITIVE_ADD
			: ADDITIVE_SUBTRACT;

		++iter;

		try(multiplicative_expression_parse(&back->expr, iter));
	}

	return ERROR_NONE;
}

void additive_expression_print_tree(AdditiveExpression *self, unsigned depth)
{
	assert(self != NULL);

	if (self->rhs_count > 0)
		depth += 1;

	multiplicative_expression_print_tree(&self->lhs, depth);
	
	for (size_t i = 0; i < self->rhs_count; ++i)
	{

		print_branch(depth - 1);

		switch (self->rhs[i].type)
		{
			case ADDITIVE_ADD:
				puts("+");
				break;

			case ADDITIVE_SUBTRACT:
				puts("-");
				break;		
		}

		multiplicative_expression_print_tree(&self->rhs[i].expr, depth);
	}
}
}
