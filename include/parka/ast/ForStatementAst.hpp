#ifndef PARKA_AST_FOR_EXPRESSION_HPP
#define PARKA_AST_FOR_EXPRESSION_HPP

#include "parka/ast/BlockStatementAst.hpp"
#include "parka/ast/DeclarationStatementAst.hpp"

namespace parka::ast
{
	class ForStatementAst: public StatementAst
	{
		fs::FileSnippet _snippet;
		DeclarationStatementAst& _declaration;
		ExpressionAst& _condition;
		StatementAst& _action;
		BlockStatementAst& _body;

	public:

		ForStatementAst(const fs::FileSnippet& snippet, DeclarationStatementAst& declaration, ExpressionAst& condition, StatementAst& action, BlockStatementAst& body):
			StatementAst(StatementType::For),
			_snippet(snippet),
			_declaration(declaration),
			_condition(condition),
			_action(action),
			_body(body)
		{}
		ForStatementAst(ForStatementAst&&) = default;
		ForStatementAst(const ForStatementAst&) = delete;

		const fs::FileSnippet& snippet() const { return _snippet; }
		const auto& declaration() const { return _declaration; }
		const auto& condition() const { return _condition; }
		const auto& action() const { return _action; }
		const auto& body() const { return _body; }
	};
}

#endif
