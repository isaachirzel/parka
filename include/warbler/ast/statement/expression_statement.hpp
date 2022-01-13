#ifndef WARBLER_AST_EXPRESSION_STATEMENT_HPP
#define WARBLER_AST_EXPRESSION_STATEMENT_HPP

// local headers
#include <warbler/token.hpp>
#include <warbler/result.hpp>
#include <warbler/ast/expression/expression.hpp>

namespace warbler
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
