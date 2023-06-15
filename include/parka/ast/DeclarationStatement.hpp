#ifndef PARKA_SYNTAX_STATEMENT_DECLARATION_SYNTAX_HPP
#define PARKA_SYNTAX_STATEMENT_DECLARATION_SYNTAX_HPP

#include "parka/ast/Expression.hpp"
#include "parka/ast/Statement.hpp"
#include "parka/ast/Variable.hpp"

namespace parka
{
	class DeclarationStatementContext : public StatementContext
	{
		VariableContext& _variable;
		ExpressionContext& _value;

	public:

		DeclarationStatementContext(VariableContext& variable, ExpressionContext& value);
		DeclarationStatementContext(DeclarationStatementContext&&) = default;
		DeclarationStatementContext(const DeclarationStatementContext&) = delete;

		StatementType statementType() const { return StatementType::Declaration; }
	};

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
