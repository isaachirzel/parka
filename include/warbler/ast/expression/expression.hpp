#ifndef WARBLER_AST_EXPRESSION_HPP
#define WARBLER_AST_EXPRESSION_HPP

#include <warbler/ast/expression/assignment_expression.hpp>

namespace warbler
{
	class Expression
	{
	private:

		AssignmentExpression _assignment;

	public:

		Expression(AssignmentExpression&& assignment);

		static Result<Expression> parse(TokenIterator& iter);

		void print_tree(u32 depth = 0);
	};
}

#endif
