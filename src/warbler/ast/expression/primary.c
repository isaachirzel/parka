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
	assert(self != NULL);

	self->type = PRIMARY_EXPRESSION;
	self->expression = NULL;
}

void primary_expression_free(PrimaryExpression *self)
{
	assert(self != NULL);

	switch (self->type)
	{
		case PRIMARY_IDENTIFIER:
			identifier_free(&self->identifier);
			break;

		case PRIMARY_CONSTANT:
			constant_free(&self->constant);
			break;

		case PRIMARY_EXPRESSION:
			if (self->expression)
				expression_free(self->expression);
			
			free(self->expression);
			break;
	}
}

static inline Error try_primary_expression_parse(PrimaryExpression *self, TokenIterator *iter)
{
	Error error;

	switch (iter->token->type)
	{
		case TOKEN_IDENTIFIER:
			self->type = PRIMARY_IDENTIFIER;

			if ((error = identifier_parse(&self->identifier, iter)))
				return error;
			debugf("identifier: %s\n", self->identifier.text);
			debug("current token: ");
			token_println(iter->token);

			break;

		case TOKEN_LPAREN:
			self->type = PRIMARY_EXPRESSION;
			++iter->token;
			self->expression = malloc(sizeof(Expression));

			if (!self->expression)
				return ERROR_MEMORY;

			if ((error = expression_parse(self->expression, iter)))
				return error;
			break;

		default:
			self->type = PRIMARY_CONSTANT;

			if ((error = constant_parse(&self->constant, iter)))
				return error;
			break;
	}

	return ERROR_NONE;
}

Error primary_expression_parse(PrimaryExpression *self, TokenIterator *iter)
{
	assert(self != NULL);
	assert(iter != NULL);

	primary_expression_init(self);

	Error error = try_primary_expression_parse(self, iter);

	if (error)
		primary_expression_free(self);

	return error;
}

void primary_expression_print_tree(PrimaryExpression *self, unsigned depth)
{
	switch (self->type)
	{
		case PRIMARY_IDENTIFIER:
			identifier_print_tree(&self->identifier, depth);
			break;

		case PRIMARY_CONSTANT:
			constant_print_tree(&self->constant, depth);
			break;

		case PRIMARY_EXPRESSION:
			assert(false && " expression_print_tree() not implemented");
			break;
	}
}
