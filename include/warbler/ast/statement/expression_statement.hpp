#ifndef WARBLER_AST_EXPRESSION_STATEMENT_HPP
#define WARBLER_AST_EXPRESSION_STATEMENT_HPP

// local headers
#include <warbler/token.hpp>
#include <warbler/util/result.hpp>
#include <warbler/ast/expression/expression.hpp>
#include <warbler/ast/expression/conditional_expression.hpp>

namespace warbler::ast
{
	class ExpressionStatement
	{
	private:

		Expression _expression;

	public:

		ExpressionStatement(Expression&& expression);

		static Result<ExpressionStatement> parse(TokenIterator& iter);

		void print_tree(u32 depth = 0) const;
	};
}

#endif
