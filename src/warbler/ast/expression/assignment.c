#include <warbler/ast/expression/assignment.h>

// standard headers
#include <stdlib.h>

void assignment_expression_init(AssignmentExpression *assignment)
{
	assert(assignment != NULL);

	assignment->lhs = malloc(sizeof(*assignment->lhs));
	assignment->rhs = malloc(sizeof(*assignment->rhs));
	assignment->type = ASSIGN_NONE;
}

void assignment_expression_free(AssignmentExpression *assignment)
{
	assert(assignment != NULL);

	if (assignment->lhs)
		prefix_expression_free(assignment->lhs);

	if (assignment->rhs)
		conditional_expression_free(assignment->rhs);

	free(assignment->lhs);
	free(assignment->rhs);
}

static inline Error try_assignment_expression_parse(AssignmentExpression *assignment, TokenIterator *iter)
{
	Error error;
	if ((error = prefix_expression_parse(assignment->lhs, iter)))
		return error;

	switch (iter->token->type)
	{
		case TOKEN_BECOME_ASSIGN:
			assignment->type = ASSIGN_BECOME;
			break;

		default:
			return ERROR_NONE;
	}

	++iter->token;

	error = conditional_expression_parse(assignment->rhs, iter);

	return error;
}

Error assignment_expression_parse(AssignmentExpression *assignment, TokenIterator *iter)
{
	assert(assignment != NULL);
	assert(iter != NULL);

	assignment_expression_init(assignment);

	Error error = try_assignment_expression_parse(assignment, iter);

	if (error)
		assignment_expression_free(assignment);

	return error;
}
