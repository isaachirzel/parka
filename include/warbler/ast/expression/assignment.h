#ifndef WARBLER_AST_ASSIGNMENT_EXPRESSION_H
#define WARBLER_AST_ASSIGNMENT_EXPRESSION_H

// local headers
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

typedef struct Assignment
{
	AssignmentType type;
	PrefixExpression *left;
	ConditionalExpression *right;
} Assignment;

void assignment_init(Assignment *assignment);
void assignment_free(Assignment *assignment);
Error assignment_parse(Assignment *assignment, TokenIterator *iter);

#endif
