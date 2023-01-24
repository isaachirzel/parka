#include "warbler/ast/expression/assignment.h"
#include "warbler/ast/expression/additive.h"
#include "warbler/ast/expression/conditional.h"
#include "warbler/validator.h"

bool parseAssignment(Expression *out, Token *token)
{
	Assignment node = { 0 };

	if (!parseConditionalExpression(&node.lhs, token))
		goto error;

	AssignmentType type;
	switch (token->type)
	{
		case TOKEN_ASSIGN:
			type = ASSIGNMENT_BECOME;
			break;

		case TOKEN_MULTIPLY_ASSIGN:
			type = ASSIGNMENT_MULTIPLY;
			break;

		case TOKEN_DIVIDE_ASSIGN:
			type = ASSIGNMENT_DIVIDE;
			break;

		case TOKEN_MODULUS_ASSIGN:
			type = ASSIGNMENT_MODULUS;
			break;

		case TOKEN_ADD_ASSIGN:
			type = ASSIGNMENT_ADD;
			break;

		case TOKEN_SUBTRACT_ASSIGN:
			type = ASSIGNMENT_SUBTRACT;
			break;

		case TOKEN_LEFT_BIT_SHIFT_ASSIGN:
			type = ASSIGNMENT_LEFT_BIT_SHIFT;
			break;

		case TOKEN_RIGHT_BIT_SHIFT_ASSIGN:
			type = ASSIGNMENT_RIGHT_BIT_SHIFT;
			break;

		case TOKEN_BITWISE_AND_ASSIGN:
			type = ASSIGNMENT_BITWISE_AND;
			break;

		case TOKEN_BITWISE_OR_ASSIGN:
			type = ASSIGNMENT_BITWISE_OR;
			break;

		case TOKEN_BITWISE_XOR_ASSIGN:
			type = ASSIGNMENT_BITWISE_XOR;
			break;
		
		default:
			*out = node.lhs;
			return true;
	}

	node.type = type;

	incrementToken(token);

	if (!parseConditionalExpression(&node.rhs, token))
		goto error;

	return true;
	
error:

	assignmentFree(&node);
	return false;
}

bool validateAssignment(Assignment *node, LocalSymbolTable *localTable)
{
	assert(node != NULL);
	assert(localTable != NULL);

	bool success = true;

	if (!validateExpression(&node->lhs, localTable))
		success = false;

	if (!validateExpression(&node->rhs, localTable))
		success = false;

	// TODO: validate type of assignment

	return success;
}

void assignmentFree(Assignment *node)
{
	expressionFree(&node->lhs);
	expressionFree(&node->rhs);
}
