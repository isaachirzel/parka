#include <warbler/ast/expression/assignment.h>

// standard headers
#include <stdlib.h>

void assignment_expression_init(AssignmentExpression *self)
{
	assert(self != NULL);

	primary_expression_init(&self->lhs);
	self->rhs = NULL;
	self->type = ASSIGN_NONE;
}

void assignment_expression_free(AssignmentExpression *self)
{
	assert(self != NULL);

	primary_expression_free(&self->lhs);

	if (self->type != ASSIGN_NONE)
		conditional_expression_free(self->rhs);

	free(self->rhs);
}

static inline Error try_assignment_expression_parse(AssignmentExpression *self, TokenIterator *iter)
{
	Error error;

	if ((error = primary_expression_parse(&self->lhs, iter)))
		return error;

	switch (iter->token->type)
	{
		case TOKEN_ASSIGN:
			self->type = ASSIGN_BECOME;
			break;

		case TOKEN_MULTIPLY_ASSIGN:
			self->type = ASSIGN_MULTIPLY;
			break;

		case TOKEN_DIVIDE_ASSIGN:
			self->type = ASSIGN_DIVIDE;
			break;

		case TOKEN_MODULUS_ASSIGN:
			self->type = ASSIGN_MODULUS;
			break;

		case TOKEN_ADD_ASSIGN:
			self->type = ASSIGN_ADD;
			break;

		case TOKEN_SUBTRACT_ASSIGN:
			self->type = ASSIGN_SUBTRACT;
			break;

		case TOKEN_LSHIFT_ASSIGN:
			self->type = ASSIGN_LSHIFT;
			break;

		case TOKEN_RSHIFT_ASSIGN:
			self->type = ASSIGN_RSHIFT;
			break;

		case TOKEN_BITAND_ASSIGN:
			self->type = ASSIGN_BITWISE_AND;
			break;

		case TOKEN_BITOR_ASSIGN:
			self->type = ASSIGN_BITWISE_OR;
			break;

		case TOKEN_BITXOR_ASSIGN:
			self->type = ASSIGN_BITWISE_XOR;
			break;

		default:
			self->type = ASSIGN_NONE;
			return ERROR_NONE;;
	}

	++iter->token;

	self->rhs = malloc(sizeof(*self->rhs));

	if ((error = conditional_expression_parse(self->rhs, iter)))
		return error;

	return ERROR_NONE;
}

Error assignment_expression_parse(AssignmentExpression *self, TokenIterator *iter)
{
	assert(self != NULL);
	assert(iter != NULL);

	assignment_expression_init(self);

	Error error = try_assignment_expression_parse(self, iter);

	if (error)
		assignment_expression_free(self);

	return error;
}

void assignment_expression_print_tree(AssignmentExpression *self, unsigned depth)
{
	assert(false && __func__);
}
