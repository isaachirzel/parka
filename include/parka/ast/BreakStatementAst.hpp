#ifndef PARKA_AST_BREAK_STATEMENT_AST_HPP
#define PARKA_AST_BREAK_STATEMENT_AST_HPP

#include "parka/ast/StatementAst.hpp"
#include "parka/fs/FileSnippet.hpp"

namespace parka::ast
{
	class BreakStatementAst: public StatementAst
	{
		fs::FileSnippet _snippet;

	public:

		BreakStatementAst(const fs::FileSnippet& snippet):
			StatementAst(StatementType::Break),
			_snippet(snippet)
		{}
		BreakStatementAst(BreakStatementAst&&) = default;
		BreakStatementAst(const BreakStatementAst&) = delete;

		const fs::FileSnippet& snippet() const { return _snippet; }
	};
}

#endif
