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

		DeclarationStatementContext(VariableContext& variable, ExpressionContext& value) :
		_variable(variable),
		_value(value)
		{}
		DeclarationStatementContext(DeclarationStatementContext&&) = default;
		DeclarationStatementContext(const DeclarationStatementContext&) = delete;

		StatementType statementType() const { return StatementType::Declaration; }
	};

	class DeclarationStatementSyntax : public StatementSyntax
	{
		Snippet _snippet;
		VariableSyntax& _variable;
		ExpressionSyntax& _value;

	public:

		DeclarationStatementSyntax(const Snippet& snippet, VariableSyntax& variable, ExpressionSyntax& value) :
		_snippet(snippet),
		_variable(variable),
		_value(value)
		{}
		DeclarationStatementSyntax(DeclarationStatementSyntax&&) = default;
		DeclarationStatementSyntax(const DeclarationStatementSyntax&) = delete;

		static StatementSyntax *parse(Token& token);
		StatementContext *validate(SymbolTable& symbolTable);

		StatementType statementType() const { return StatementType::Declaration; }
		const Snippet& snippet() const { return _snippet; }
		const auto& variable() const { return _variable; }
		const auto& value() const { return _value; }
	};
}

#endif
