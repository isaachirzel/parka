#ifndef PARKA_AST_BREAK_STATEMENT_AST_HPP
#define PARKA_AST_BREAK_STATEMENT_AST_HPP

#include "parka/ast/StatementAst.hpp"
#include "parka/file/Snippet.hpp"

namespace parka::ast
{
	class BreakStatementAst: public StatementAst
	{
		Snippet _snippet;

	public:

		BreakStatementAst(const Snippet& snippet):
			StatementAst(StatementType::Break),
			_snippet(snippet)
		{}
		BreakStatementAst(BreakStatementAst&&) = default;
		BreakStatementAst(const BreakStatementAst&) = delete;

		const Snippet& snippet() const { return _snippet; }
	};
}

#endif
