#ifndef WARBLER_AST_EXPRESSION_ASSIGNMENT_H
#define WARBLER_AST_EXPRESSION_ASSIGNMENT_H

// local headers
#include <warbler/ast/expression/conditional.h>
#include <warbler/ast/expression/prefix.h>

typedef enum AssignmentType
{
	ASSIGN_NONE,
	ASSIGN_BECOME,
	ASSIGN_MULTIPLY,
	ASSIGN_DIVIDE,
	ASSIGN_MODULUS,
	ASSIGN_ADD,
	ASSIGN_SUBTRACT,
	ASSIGN_LSHIFT,
	ASSIGN_RSHIFT,
	ASSIGN_BITWISE_AND,
	ASSIGN_BITWISE_OR,
	ASSIGN_BITWISE_XOR,
	ASSIGN_BOOLEAN_AND,
	ASSIGN_BOOLEAN_XOR,
	ASSIGN_BOOLEAN_OR
} AssignmentType;

typedef struct AssignmentExpression
{
	PrefixExpression *lhs;
	ConditionalExpression *rhs;
	AssignmentType type;
} AssignmentExpression;

void assignment_expression_init(AssignmentExpression *assignment);
void assignment_expression_free(AssignmentExpression *assignment);
Error assignment_expression_parse(AssignmentExpression *assignment, TokenIterator *iter);

#endif
