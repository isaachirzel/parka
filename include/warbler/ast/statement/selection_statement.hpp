#ifndef WARBLER_AST_STATEMENT_SELECTION_STATEMENT_HPP
#define WARBLER_AST_STATEMENT_SELECTION_STATEMENT_HPP

// local headers
#include <warbler/token.hpp>
#include <warbler/result.hpp>
#include <warbler/ast/expression/conditional_expression.hpp>

namespace warbler
{
	class SelectionStatement
	{
	private:

		ConditionalExpression _expr;

	public:

		SelectionStatement(ConditionalExpression&& expr);

		static Result<SelectionStatement> parse(TokenIterator& iter);

		void print_tree(u32 depth = 0) const;
	};
}

#endif
