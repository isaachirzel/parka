#include <warbler/ast/expression/expression.hpp>
#include <warbler/ast/argument.hpp>

// local headers
#include <warbler/print.hpp>

// standard headers
#include <stdlib.h>
#include <assert.h>

namespace warbler
{
void argument_init(Argument *self)
{
	assert(self);

	expression_init(self->expr);
}

void argument_list_init(ArgumentList *self)
{
	assert(self);

	*self = (ArgumentList)
	{
		.arguments = NULL,
		.argument_count = 0
	};
}

void argument_free(Argument *self)
{
	if (!self)
		return;

	expression_free(self->expr);
	free(self->expr);
}

void argument_list_free(ArgumentList *self)
{
	if (!self)
		return;

	for (size_t i = 0; i < self->argument_count; ++i)
		argument_free(self->arguments + i);

	free(self->arguments);
}

Error argument_parse(Argument *self, TokenIterator& iter)
{
	assert(self);

	self->expr = new Expression();

	if (!self->expr)
		return ERROR_MEMORY;

	try(expression_parse(self->expr, iter));

	return ERROR_NONE;
}

static Argument *push_argument(ArgumentList *self)
{
	size_t new_size = (self->argument_count + 1) * sizeof(Argument);
	Argument *tmp = (Argument*)realloc(self->arguments, new_size);

	if (!tmp)
		return NULL;

	Argument *out = tmp + self->argument_count;

	self->arguments = tmp;
	++self->argument_count;

	return out;
}

Error argument_list_parse(ArgumentList *self, TokenIterator& iter)
{
	assert(self != NULL);

	if (iter->type != TOKEN_LPAREN)
	{
		errortf(*iter, "expected '(' at start of argument list but got: %t", &iter);
		return ERROR_ARGUMENT;
	}

	if (iter[1].type != TOKEN_RPAREN)
	{
		do
		{
			++iter;

			Argument *back = push_argument(self);

			if (!back)
				return ERROR_MEMORY;

			try(argument_parse(back, iter));
		}
		while (iter->type == TOKEN_COMMA);

		if (iter->type != TOKEN_RPAREN)
		{
			errortf(*iter, "expected ')' or ',' but got", &iter);
			return ERROR_ARGUMENT;
		}
	}

	++iter;

	return ERROR_NONE;
}

void argument_print_tree(Argument *self, unsigned depth)
{
	assert(self);

	expression_print_tree(self->expr, depth);
}

void argument_list_print_tree(ArgumentList *self, unsigned depth)
{
	print_branch(depth);
	puts("()");

	//return;

	for (size_t i = 0; i < self->argument_count; ++i)
		argument_print_tree(self->arguments + i, depth + 1);
}
}
