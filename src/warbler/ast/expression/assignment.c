#include <warbler/ast/expression/assignment.h>

// local headers
#include <warbler/print.h>

// standard headers
#include <stdlib.h>

void assignment_expression_init(AssignmentExpression *self)
{
	assert(self);

	primary_expression_init(&self->lhs);
	self->rhs = NULL;
	self->type = ASSIGN_NONE;
}

void assignment_expression_free(AssignmentExpression *self)
{
	if (!self)
		return;

	primary_expression_free(&self->lhs);

	if (self->type != ASSIGN_NONE)
		conditional_expression_free(self->rhs);

	free(self->rhs);
}

Error assignment_expression_parse(AssignmentExpression *self, TokenIterator *iter)
{
	assert(self);
	assert(iter);

	assignment_expression_init(self);
	
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

void assignment_expression_print_tree(AssignmentExpression *self, unsigned depth)
{
	assert(self != NULL);

	primary_expression_print_tree(&self->lhs, depth);

	print_branch(depth + 1);

	const char *symbol;
	switch (self->type)
	{
		case ASSIGN_NONE:
			return;

		case ASSIGN_BECOME:
			symbol = "=";
			break;

		case ASSIGN_MULTIPLY:
			symbol = "*=";
			break;

		case ASSIGN_DIVIDE:
			symbol = "/=";
			break;

		case ASSIGN_MODULUS:
			symbol = "%=";
			break;

		case ASSIGN_ADD:
			symbol = "+=";
			break;

		case ASSIGN_SUBTRACT:
			symbol = "-=";
			break;

		case ASSIGN_LSHIFT:
			symbol = "<<=";
			break;

		case ASSIGN_RSHIFT:
			symbol = ">>=";
			break;

		case ASSIGN_BITWISE_AND:
			symbol = "&=";
			break;

		case ASSIGN_BITWISE_OR:
			symbol = "|=";
			break;

		case ASSIGN_BITWISE_XOR:
			symbol = "^=";
			break;
	}

	print_branch(depth + 1);
	puts(symbol);

	conditional_expression_print_tree(self->rhs, depth + 1);
}
