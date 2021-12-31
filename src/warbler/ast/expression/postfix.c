#include <warbler/ast/expression/postfix.h>

// local headers
#include <warbler/print.h>
#include <warbler/ast/expression/expression.h>

// standard headers
#include <assert.h>
#include <stdlib.h>

void postfix_init(Postfix *self)
{
	assert(self);

	*self = (Postfix)
	{
		.expression = NULL,
		.type = POSTFIX_INDEX
	};
}

void postfix_free(Postfix *self)
{
	assert(self);

	switch (self->type)
	{
		case POSTFIX_INDEX:
			if (self->expression)
				expression_free(self->expression);
			
			free(self->expression);
			break;

		case POSTFIX_CALL:
			parameter_list_free(&self->parameters);
			break;

		case POSTFIX_MEMBER:
			identifier_free(&self->identifier);
			break;
	}
}

static Error try_postfix_parse(Postfix *self, TokenIterator *iter)
{
	postfix_init(self);

	Error error;

	switch (iter->token->type)
	{
		case TOKEN_LBRACK:
			++iter->token;
			self->expression = malloc(sizeof(Expression));

			if (!self->expression)
				return ERROR_MEMORY;

			if ((error = expression_parse(self->expression, iter)))
				return error;

			if (iter->token->type != TOKEN_RBRACK)
			{
				print_token_error("expected ']' after index operation but got: ", iter->token);
				return ERROR_ARGUMENT;
			}
			break;

		case TOKEN_LPAREN:
			if ((error = parameter_list_parse(&self->parameters, iter)))
				return error;
			break;

		case TOKEN_DOT:
			++iter->token;

			if ((error = identifier_parse(&self->identifier, iter)))
				return error;
			break;

		default:
			print_error("expected postfix but got: ");
			token_println(iter->token);
			return ERROR_ARGUMENT;
	}

	return ERROR_NONE;
}

Error postfix_parse(Postfix *self, TokenIterator *iter)
{
	assert(self);
	assert(iter);

	Error error = try_postfix_parse(self, iter);

	if (error)
		postfix_free(self);

	return error;
}

void postfix_print_tree(Postfix *self, unsigned depth)
{
	assert(self);

	print_branch(depth);

	switch (self->type)
	{
		case POSTFIX_INDEX:
			puts("[]");
			expression_print_tree(self->expression, depth + 1);
			break;

		case POSTFIX_CALL:
			puts("()");
			parameter_list_print_tree(&self->parameters, depth + 1);
			break;

		case POSTFIX_MEMBER:
			puts(".");
			identifier_print_tree(&self->identifier, depth + 1);
			break;
	}
}

void postfix_list_init(PostfixList *self)
{
	assert(self);

	*self = (PostfixList)
	{
		.data = NULL,
		.count = 0
	};
}

void postfix_list_free(PostfixList *self)
{
	assert(self);

	for (size_t i = 0; i < self->count; ++i)
		postfix_free(self->data + i);

	free(self->data);
}

static Postfix *postfix_list_push(PostfixList *self)
{
	size_t new_size = (self->count + 1) * sizeof(Postfix);
	Postfix *tmp = realloc(self->data, new_size);

	if (!tmp)
		return NULL;

	Postfix *back = tmp + self->count;

	self->data = tmp;
	++self->count;

	return back;
}

static Error try_postfix_list_parse(PostfixList *self, TokenIterator *iter)
{
	Error error;
	TokenType type = iter->token->type;

	while (type == TOKEN_DOT || type == TOKEN_LPAREN || type == TOKEN_LBRACK)
	{
		Postfix *back = postfix_list_push(self);

		if (!tmp)
			return ERROR_MEMORY;

		if ((error = try_postfix_parse(back, iter)))
			return error;

		type = iter->token->type;
	}

	return ERROR_NONE;
}

Error postfix_list_parse(PostfixList *self, TokenIterator *iter)
{
	assert(self);
	assert(iter);

	postfix_list_init(self);

	Error error = try_postfix_list_parse(self, iter);

	if (error)
		postfix_list_free(self);

	return error;
}

void postfix_list_print_tree(PostfixList *self, unsigned depth)
{
	assert(self);

	for (size_t i = 0; i < self->count; ++i)
	{
		postfix_print_tree(self->data + i, depth + 1);
	}
}
