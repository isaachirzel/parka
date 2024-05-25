#ifndef PARKA_AST_CONTINUE_STATEMENT_AST_HPP
#define PARKA_AST_CONTINUE_STATEMENT_AST_HPP

#include "parka/ast/StatementAst.hpp"
#include "parka/file/Snippet.hpp"

namespace parka::ast
{
	class ContinueStatementAst: public StatementAst
	{
		Snippet _snippet;

	public:

		ContinueStatementAst(const Snippet& snippet):
			StatementAst(StatementType::Continue),
			_snippet(snippet)
		{}
		ContinueStatementAst(ContinueStatementAst&&) = default;
		ContinueStatementAst(const ContinueStatementAst&) = delete;

		const Snippet& snippet() const { return _snippet; }
	};
}

#endif
