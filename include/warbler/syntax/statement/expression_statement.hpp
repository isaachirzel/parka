#ifndef WARBLER_SYNTAX_EXPRESSION_STATEMENT_HPP
#define WARBLER_SYNTAX_EXPRESSION_STATEMENT_HPP

// local headers
#include <warbler/lexicon/token.hpp>
#include <warbler/util/result.hpp>
#include <warbler/syntax/statement/statement.hpp>
#include <warbler/syntax/expression/expression.hpp>
#include <warbler/syntax/expression/conditional_expression.hpp>

namespace warbler::syntax
{
	class ExpressionStatement : public Statement
	{
	private:

		Ptr<Expression> _expression;

	public:

		ExpressionStatement(Ptr<Expression>&& expression);

		static Result<ExpressionStatement> parse(lexicon::Token& token);

		bool validate(semantics::Context& context);
		void print_tree(u32 depth = 0) const;
	};
}

#endif
