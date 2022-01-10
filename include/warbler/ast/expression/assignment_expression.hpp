#ifndef WARBLER_AST_EXPRESSION_ASSIGNMENT_HPP
#define WARBLER_AST_EXPRESSION_ASSIGNMENT_HPP

// local headers
#include <warbler/ast/expression/primary_expression.hpp>
#include <warbler/ast/expression/conditional_expression.hpp>
#include <warbler/ast/expression/prefix.hpp>
namespace warbler
{
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
	ASSIGN_BITWISE_XOR
} AssignmentType;

typedef struct AssignmentExpression
{
	PrimaryExpression lhs;
	ConditionalExpression *rhs;
	AssignmentType type;
} AssignmentExpression;

void assignment_expression_init(AssignmentExpression *self);
void assignment_expression_free(AssignmentExpression *self);
Error assignment_expression_parse(AssignmentExpression *self, TokenIterator& iter);
void assignment_expression_print_tree(AssignmentExpression *self, unsigned depth);
}
#endif
