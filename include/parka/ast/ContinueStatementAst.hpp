#ifndef PARKA_AST_CONTINUE_STATEMENT_AST_HPP
#define PARKA_AST_CONTINUE_STATEMENT_AST_HPP

#include "parka/ast/StatementAst.hpp"
#include "parka/fs/FileSnippet.hpp"

namespace parka::ast
{
	class ContinueStatementAst: public StatementAst
	{
		fs::FileSnippet _snippet;

	public:

		ContinueStatementAst(const fs::FileSnippet& snippet):
			StatementAst(StatementType::Continue),
			_snippet(snippet)
		{}
		ContinueStatementAst(ContinueStatementAst&&) = default;
		ContinueStatementAst(const ContinueStatementAst&) = delete;

		const fs::FileSnippet& snippet() const { return _snippet; }
	};
}

#endif
