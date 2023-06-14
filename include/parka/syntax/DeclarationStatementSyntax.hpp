#ifndef PARKA_SYNTAX_STATEMENT_DECLARATION_SYNTAX_HPP
#define PARKA_SYNTAX_STATEMENT_DECLARATION_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/syntax/StatementSyntax.hpp"
#include "parka/syntax/VariableSyntax.hpp"

namespace parka
{
	class DeclarationStatementSyntax : public StatementSyntax
	{
		VariableSyntax& _variable;
		ExpressionSyntax& _value;

	public:

		DeclarationStatementSyntax(VariableSyntax& variable, ExpressionSyntax& value);
		DeclarationStatementSyntax(DeclarationStatementSyntax&&) = default;
		DeclarationStatementSyntax(const DeclarationStatementSyntax&) = delete;

		static StatementSyntax *parse(Token& token);
		StatementContext *validate(SymbolTable& symbolTable);

		StatementType statementType() const { return StatementType::Declaration; }
		const auto& variable() const { return _variable; }
		const auto& value() const { return _value; }
	};
}

#endif
