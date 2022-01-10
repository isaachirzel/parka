#ifndef WARBLER_AST_EXPRESSION_HPP
#define WARBLER_AST_EXPRESSION_HPP

#include <warbler/ast/expression/assignment_expression.hpp>

namespace warbler
{
	typedef struct Expression
	{
		AssignmentExpression assignment;
	} Expression;

	void expression_init(Expression *self);
	void expression_free(Expression *self);
	Error expression_parse(Expression *self, TokenIterator& iter);
	void expression_print_tree(Expression *self, unsigned depth);
}

#endif
