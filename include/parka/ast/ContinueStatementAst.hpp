#ifndef PARKA_AST_CONTINUE_STATEMENT_AST_HPP
#define PARKA_AST_CONTINUE_STATEMENT_AST_HPP

#include "parka/ast/KeywordAst.hpp"
#include "parka/ast/StatementAst.hpp"

namespace parka::ast
{
	class ContinueStatementAst: public StatementAst
	{
		KeywordAst _keyword;

	public:

		ContinueStatementAst(KeywordAst&& keyword):
			StatementAst(StatementType::Continue),
			_keyword(std::move(keyword))
		{}
		ContinueStatementAst(ContinueStatementAst&&) = default;
		ContinueStatementAst(const ContinueStatementAst&) = delete;

		const Snippet& snippet() const { return _keyword.snippet(); }
		const auto& keyword() const { return _keyword; }
	};
}

#endif
