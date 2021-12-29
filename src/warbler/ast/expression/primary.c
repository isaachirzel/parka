#include <warbler/ast/expression/primary.h>

// local headers
#include <warbler/ast/expression/expression.h>

// standard headers
#include <assert.h>
#include <stdlib.h>

void expression_free(struct Expression *expression);

void primary_expression_init(PrimaryExpression *self)
{
	assert(self != NULL);

	self->type = PRIMARY_IDENTIFIER;
	self->identifier = NULL;
}

void primary_expression_free(PrimaryExpression *self)
{
	assert(self != NULL);

	switch (self->type)
	{
		case PRIMARY_IDENTIFIER:
			if (self->identifier)
				identifier_free(self->identifier);

			free(self->identifier);
			break;

		case PRIMARY_CONSTANT:
			if (self->constant)
				constant_free(self->constant);

			free(self->constant);
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

	printf("Type: %d\n", (int)iter->token->type);

	switch (iter->token->type)
	{
		case TOKEN_IDENTIFIER:
			self->type = PRIMARY_IDENTIFIER;
			self->identifier = malloc(sizeof(Identifier));

			if (!self->identifier)
				return ERROR_MEMORY;

			if ((error = identifier_parse(self->identifier, iter)))
				return error;
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
			puts("constant parse");
			self->type = PRIMARY_CONSTANT;
			self->constant = malloc(sizeof(Constant));

			if (!self->constant)
				return ERROR_MEMORY;

			if ((error = constant_parse(self->constant, iter)))
				return error;
			break;
	}

	return ERROR_NONE;
}

Error primary_expression_parse(PrimaryExpression *self, TokenIterator *iter)
{
	assert(self != NULL);
	assert(iter != NULL);

	puts("primary expression parse");

	primary_expression_init(self);

	Error error = try_primary_expression_parse(self, iter);

	if (error)
		primary_expression_free(self);

	return error;
}
