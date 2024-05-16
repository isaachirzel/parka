#ifndef PARKA_AST_IF_STATEMENT_AST_HPP
#define PARKA_AST_IF_STATEMENT_AST_HPP

#include "parka/ast/ExpressionAst.hpp"
#include "parka/ast/StatementAst.hpp"

namespace parka::ast
{
	class IfStatementAst: public StatementAst
	{
		Snippet _snippet;
		ExpressionAst& _condition;
		StatementAst& _thenCase;
		StatementAst* _elseCase;

	public:

		IfStatementAst(const Snippet& snippet, ExpressionAst& condition, StatementAst& thenCase, StatementAst* elseCase):
			StatementAst(StatementType::If),
			_snippet(snippet),
			_condition(condition),
			_thenCase(thenCase),
			_elseCase(elseCase)
		{}
		IfStatementAst(IfStatementAst&&) = default;
		IfStatementAst(const IfStatementAst&) = delete;

		const Snippet& snippet() const { return _snippet; }
		const auto& condition() const { return _condition; }
		const auto& thenCase() const { return _thenCase; }
		bool hasElseCase() const { return !!_elseCase; }
		const auto& elseCase() const { assert(_elseCase); return *_elseCase; }
	};
}

#endif
