#ifndef PARKA_SYNTAX_STATMENT_EXPRESSION_SYNTAX_HPP
#define PARKA_SYNTAX_STATMENT_EXPRESSION_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/syntax/StatementSyntax.hpp"
#include "parka/Token.hpp"
#include "parka/util/Optional.hpp"

#include <utility>

namespace parka
{
	class ExpressionStatementSyntax : public StatementSyntax
	{
		ExpressionSyntax& _expression;

	public:

		ExpressionStatementSyntax(ExpressionSyntax& expression) :
		_expression(expression)
		{}
		ExpressionStatementSyntax(ExpressionStatementSyntax&&) = default;
		ExpressionStatementSyntax(const ExpressionStatementSyntax&) = delete;

		static StatementSyntax *parse(Token& token);

		StatementType statementType() const { return StatementType::Expression; }
		const auto& expression() const { return _expression; }
	};
}

#endif
