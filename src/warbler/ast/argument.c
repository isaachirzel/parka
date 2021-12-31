#include <warbler/ast/expression/expression.h>
#include <warbler/ast/argument.h>

// local headers
#include <warbler/print.h>

// standard headers
#include <stdlib.h>
#include <assert.h>

void argument_init(Argument *self)
{
	assert(self);

	expression_init(&self->expr);
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

	expression_free(&self->expr);
}

void argument_list_free(ArgumentList *self)
{
	if (!self)
		return;

	for (size_t i = 0; i < self->argument_count; ++i)
	{
		argument_free(self->arguments + i);
	}

	free(self->arguments);
}

Error argument_parse(Argument *self, TokenIterator *iter)
{
	assert(self);
	assert(iter);

	Error error;

	if ((error = expression_parse(&self->expr, iter)))
	{
		expression_free(&self->expr);
		return error;
	}

	return ERROR_NONE;
}

static Argument *push_argument(ArgumentList * self)
{
	size_t new_size = (self->argument_count + 1) * sizeof(Argument);
	Argument *tmp = realloc(self->arguments, new_size);

	if (!tmp)
		return NULL;

	Argument *out = tmp + self->argument_count;

	self->arguments = tmp;
	++self->argument_count;

	return out;
}

static Error try_argument_list_parse(ArgumentList *self, TokenIterator *iter)
{
	if (iter->token->type != TOKEN_LPAREN)
	{
		print_token_error("expected '(' at start of argument list but got", iter->token);
		return ERROR_ARGUMENT;
	}

	if (iter->token[1].type != TOKEN_RPAREN)
	{
		do
		{
			++iter->token;

			Argument *back = push_argument(self);

			if (!back)
				return ERROR_MEMORY;

			Error error;

			if ((error = argument_parse(back, iter)))
				return error;
		}
		while (iter->token->type == TOKEN_COMMA);

		if (iter->token->type != TOKEN_RPAREN)
		{
			print_token_error("expected ')' or ',' but got", iter->token);
			return ERROR_ARGUMENT;
		}
	}

	++iter->token;

	return ERROR_NONE;
}

Error argument_list_parse(ArgumentList *self, TokenIterator *iter)
{
	assert(self);
	assert(iter);

	Error error = try_argument_list_parse(self, iter);

	if (error)
		argument_list_free(self);
	
	return error;
}

void argument_print_tree(Argument *self, unsigned depth)
{
	assert(self);

	expression_print_tree(&self->expr, depth);
}

void argument_list_print_tree(ArgumentList *self, unsigned depth)
{
	print_branch(depth);
	puts("()");

	for (size_t i = 0; i < self->argument_count; ++i)
	{
		argument_print_tree(self->arguments + i, depth + 1);
	}
}
