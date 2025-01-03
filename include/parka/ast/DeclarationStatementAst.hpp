#ifndef PARKA_AST_STATEMENT_DECLARATION_HPP
#define PARKA_AST_STATEMENT_DECLARATION_HPP

#include "parka/ast/ExpressionAst.hpp"
#include "parka/ast/StatementAst.hpp"
#include "parka/ast/VariableAst.hpp"

namespace parka::ast
{
	class DeclarationStatementAst: public StatementAst
	{
		fs::FileSnippet _snippet;
		VariableAst& _variable;
		ExpressionAst& _value;

	public:

		DeclarationStatementAst(const fs::FileSnippet& snippet, VariableAst& variable, ExpressionAst& value):
		StatementAst(StatementType::Declaration),
		_snippet(snippet),
		_variable(variable),
		_value(value)
		{}
		DeclarationStatementAst(DeclarationStatementAst&&) = default;
		DeclarationStatementAst(const DeclarationStatementAst&) = delete;

		const fs::FileSnippet& snippet() const { return _snippet; }
		const auto& variable() const { return _variable; }
		const auto& value() const { return _value; }
	};
}

#endif
