#ifndef PARKA_SYNTAX_STATMENT_EXPRESSION_SYNTAX_HPP
#define PARKA_SYNTAX_STATMENT_EXPRESSION_SYNTAX_HPP

#include "parka/ast/Expression.hpp"
#include "parka/ast/Statement.hpp"
#include "parka/Token.hpp"
#include "parka/util/Optional.hpp"

#include <utility>

namespace parka
{
	class ExpressionStatementSyntax : public StatementSyntax
	{
		ExpressionSyntax& _expression;

	public:

		ExpressionStatementSyntax(ExpressionSyntax& expression);
		ExpressionStatementSyntax(ExpressionStatementSyntax&&) = default;
		ExpressionStatementSyntax(const ExpressionStatementSyntax&) = delete;

		static StatementSyntax *parse(Token& token);
		StatementContext *validate(SymbolTable& symbolTable);

		StatementType statementType() const { return StatementType::Expression; }
		const auto& expression() const { return _expression; }
	};
}

#endif