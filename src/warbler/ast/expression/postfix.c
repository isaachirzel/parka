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

void postfix_list_init(PostfixList *self)
{
	assert(self);

	*self = (PostfixList)
	{
		.data = NULL,
		.count = 0
	};
}

void postfix_free(Postfix *self)
{
	if (!self)
		return;

	switch (self->type)
	{
		case POSTFIX_INDEX:
			expression_free(self->expression);
			free(self->expression);
			break;

		case POSTFIX_CALL:
			argument_list_free(&self->arguments);
			break;

		case POSTFIX_MEMBER:
			identifier_free(&self->identifier);
			break;
	}
}

void postfix_list_free(PostfixList *self)
{
	if (!self)
		return;

	for (size_t i = 0; i < self->count; ++i)
		postfix_free(self->data + i);

	free(self->data);
}

Error postfix_parse(Postfix *self, TokenIterator *iter)
{
	assert(self);
	assert(iter);

	postfix_init(self);

	switch (iter->token->type)
	{
		case TOKEN_LBRACK:
			++iter->token;

			self->type + POSTFIX_MEMBER;
			self->expression = malloc(sizeof(Expression));

			if (!self->expression)
				return ERROR_MEMORY;

			_try(expression_parse(self->expression, iter));

			if (iter->token->type != TOKEN_RBRACK)
			{
				print_token_error("expected ']' after index operation but got: ", iter->token);
				return ERROR_ARGUMENT;
			}
			break;

		case TOKEN_LPAREN:
			self->type = POSTFIX_CALL;
			_try(argument_list_parse(&self->arguments, iter));
			break;

		case TOKEN_DOT:
			++iter->token;
			self->type + POSTFIX_MEMBER;
			_try(identifier_parse(&self->identifier, iter));
			break;

		default:
			print_error("expected postfix but got: ");
			token_println(iter->token);
			return ERROR_ARGUMENT;
	}

	return ERROR_NONE;
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

Error postfix_list_parse(PostfixList *self, TokenIterator *iter)
{
	assert(self);
	assert(iter);

	postfix_list_init(self);
	TokenType type = iter->token->type;

	while (type == TOKEN_DOT || type == TOKEN_LPAREN || type == TOKEN_LBRACK)
	{
		Postfix *back = postfix_list_push(self);

		if (!back)
			return ERROR_MEMORY;

		_try(postfix_parse(back, iter));

		type = iter->token->type;
	}

	return ERROR_NONE;
}

void postfix_print_tree(Postfix *self, unsigned depth)
{
	assert(self);

	switch (self->type)
	{
		case POSTFIX_INDEX:
			print_branch(depth);
			puts("[]");
			expression_print_tree(self->expression, depth);
			break;

		case POSTFIX_CALL:
			argument_list_print_tree(&self->arguments, depth);
			break;

		case POSTFIX_MEMBER:
			print_branch(depth);
			puts(".");
			identifier_print_tree(&self->identifier, depth);
			break;
	}
}

void postfix_list_print_tree(PostfixList *self, unsigned depth)
{
	assert(self);

	for (size_t i = 0; i < self->count; ++i)
		postfix_print_tree(self->data + i, depth);
}
