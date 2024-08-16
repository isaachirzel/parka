#ifndef PARKA_AST_STATMENT_EXPRESSION_HPP
#define PARKA_AST_STATMENT_EXPRESSION_HPP

#include "parka/ast/ExpressionAst.hpp"
#include "parka/ast/StatementAst.hpp"

namespace parka::ast
{
	class ExpressionStatementAst: public StatementAst
	{
		fs::FileSnippet _snippet;
		ExpressionAst& _expression;

	public:

		ExpressionStatementAst(const fs::FileSnippet& snippet, ExpressionAst& expression):
		StatementAst(StatementType::Expression),
		_snippet(snippet),
		_expression(expression)
		{}
		ExpressionStatementAst(ExpressionStatementAst&&) = default;
		ExpressionStatementAst(const ExpressionStatementAst&) = delete;

		const fs::FileSnippet& snippet() const { return _snippet; }
		const auto& expression() const { return _expression; }
	};
}

#endif
