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
		const ExpressionSyntax& _expression;

		ExpressionStatementSyntax(const ExpressionSyntax& expression) :
		_expression(expression)
		{}

	public:

		ExpressionStatementSyntax(ExpressionStatementSyntax&&) = default;
		ExpressionStatementSyntax(const ExpressionStatementSyntax&) = delete;

		static const StatementSyntax *parse(Token& token);

		StatementType statementType() const { return StatementType::Expression; }
		const auto& expression() const { return _expression; }
	};
}

#endif
