#include <warbler/ast/expression/primary.h>

// local headers
#include <warbler/print.h>
#include <warbler/ast/expression/expression.h>

// standard headers
#include <assert.h>
#include <stdlib.h>

void expression_free(struct Expression *expression);

void primary_expression_init(PrimaryExpression *self)
{
	assert(self);

	prefix_list_init(&self->prefixes);
	postfix_list_init(&self->postfixes);

	self->expression = NULL;
	self->type = PRIMARY_EXPRESSION;
}

void primary_expression_free(PrimaryExpression *self)
{
	if (!self)
		return;

	prefix_list_free(&self->prefixes);
	postfix_list_free(&self->postfixes);

	switch (self->type)
	{
		case PRIMARY_IDENTIFIER:
			identifier_free(&self->identifier);
			break;

		case PRIMARY_CONSTANT:
			constant_free(&self->constant);
			break;

		case PRIMARY_EXPRESSION:
			expression_free(self->expression);
			
			free(self->expression);
			break;
	}
}

Error primary_expression_parse(PrimaryExpression *self, TokenIterator *iter)
{
	assert(self);
	assert(iter);

	primary_expression_init(self);

	_try(prefix_list_parse(&self->prefixes, iter));

	switch (iter->token->type)
	{
		case TOKEN_IDENTIFIER:
			self->type = PRIMARY_IDENTIFIER;
			_try(identifier_parse(&self->identifier, iter));
			break;

		case TOKEN_LPAREN:
			self->type = PRIMARY_EXPRESSION;
			++iter->token;
			self->expression = malloc(sizeof(Expression));

			if (!self->expression)
				return ERROR_MEMORY;

			_try(expression_parse(self->expression, iter));
			break;

		default:
			self->type = PRIMARY_CONSTANT;
			_try(constant_parse(&self->constant, iter));
			break;
	}

	_try(postfix_list_parse(&self->postfixes, iter));

	return ERROR_NONE;
}

void primary_expression_print_tree(PrimaryExpression *self, unsigned depth)
{
	assert(self);

	// if (self->prefixes.count > 0)
	// 	depth += 1;

	// prefix_list_print_tree(&self->prefixes, depth - 1);

	switch (self->type)
	{
		case PRIMARY_IDENTIFIER:
			identifier_print_tree(&self->identifier, depth);
			break;

		case PRIMARY_CONSTANT:
			constant_print_tree(&self->constant, depth);
			break;

		case PRIMARY_EXPRESSION:
			expression_print_tree(self->expression, depth);
			break;
	}

	postfix_list_print_tree(&self->postfixes, depth + 1);
}
