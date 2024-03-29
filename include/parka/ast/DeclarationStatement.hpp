#ifndef PARKA_AST_STATEMENT_DECLARATION_HPP
#define PARKA_AST_STATEMENT_DECLARATION_HPP

#include "parka/ast/Expression.hpp"
#include "parka/ast/Statement.hpp"
#include "parka/ast/Variable.hpp"

namespace parka::ast
{
	class DeclarationStatementAst: public StatementAst
	{
		Snippet _snippet;
		VariableAst& _variable;
		ExpressionAst& _value;

	public:

		DeclarationStatementAst(const Snippet& snippet, VariableAst& variable, ExpressionAst& value):
		StatementAst(StatementType::Declaration),
		_snippet(snippet),
		_variable(variable),
		_value(value)
		{}
		DeclarationStatementAst(DeclarationStatementAst&&) = default;
		DeclarationStatementAst(const DeclarationStatementAst&) = delete;

		const Snippet& snippet() const { return _snippet; }
		const auto& variable() const { return _variable; }
		const auto& value() const { return _value; }
	};
}

#endif
