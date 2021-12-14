#include <warbler/ast/expression/assignment.h>

void assignment_init(Assignment *assignment)
{
	assignment->type = ASSIGN_NONE;
	assignment->left = NULL;
	assignment->right = NULL;
}

void assignment_free(Assignment *assignment)
{
	prefix_expression_free(assignment->left);
	prefix_expression_free(assignment->right);
}

Error assignment_parse(Assignment *assignment, TokenIterator *iter)
{
	assignment_init(assignment);

	Error error;
	if ((error = prefix_expression_parse(assignment->left, iter)))
	{
		assignment_free(assignment);
		return error;
	}

	switch (iter->token->type)
	{
		case TOKEN_EQUALS:
			assignment->type = ASSIGN_BECOME;
			break;

		default:
			print_error("invalid assignment type: ");
			string_println(&iter->token->string);
			assignment_free(assignment);
			return ERROR_ARGUMENT;
	}

	++iter->token;

	if ((error = prefix_expression_parse(assignment->right, iter)))
	{
		assignment_free(assignment);
		return error;
	}

	return ERROR_NONE;
}
