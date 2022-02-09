#ifndef WARBLER_AST_EXPRESSION_STATEMENT_HPP
#define WARBLER_AST_EXPRESSION_STATEMENT_HPP

// local headers
#include <warbler/token.hpp>
#include <warbler/util/result.hpp>
#include <warbler/ast/statement/statement.hpp>
#include <warbler/ast/expression/expression.hpp>
#include <warbler/ast/expression/conditional_expression.hpp>
#include <warbler/semantics/context.hpp>

namespace warbler::ast
{
	class ExpressionStatement : public Statement
	{
	private:

		Ptr<Expression> _expression;

	public:

		ExpressionStatement(Ptr<Expression>&& expression);

		static Result<ExpressionStatement> parse(TokenIterator& iter);

		bool validate(semantics::Context& context);
		void print_tree(u32 depth = 0) const;
	};
}

#endif
