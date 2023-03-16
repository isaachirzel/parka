#ifndef PARKA_AST_EXPRESSION_ASSIGNMENT_H
#define PARKA_AST_EXPRESSION_ASSIGNMENT_H

#include "parka/ast/expression/expression.h"

typedef enum AssignmentType
{
	ASSIGNMENT_BECOME,
	ASSIGNMENT_MULTIPLY,
	ASSIGNMENT_DIVIDE,
	ASSIGNMENT_MODULUS,
	ASSIGNMENT_ADD,
	ASSIGNMENT_SUBTRACT,
	ASSIGNMENT_LEFT_BIT_SHIFT,
	ASSIGNMENT_RIGHT_BIT_SHIFT,
	ASSIGNMENT_BITWISE_AND,
	ASSIGNMENT_BITWISE_OR,
	ASSIGNMENT_BITWISE_XOR
} AssignmentType;

typedef struct Assignment
{
	Expression lhs;
	Expression rhs;
	AssignmentType type;
} Assignment;

bool parseAssignment(Expression *out, Token *token);
bool validateAssignment(Assignment *node, LocalSymbolTable *localTable);
void assignmentFree(Assignment *node);

#endif
