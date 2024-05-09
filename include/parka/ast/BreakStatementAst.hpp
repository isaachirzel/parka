#ifndef PARKA_AST_BREAK_STATEMENT_AST_HPP
#define PARKA_AST_BREAK_STATEMENT_AST_HPP

#include "parka/ast/KeywordAst.hpp"
#include "parka/ast/StatementAst.hpp"

namespace parka::ast
{
	class BreakStatementAst: public StatementAst
	{
		KeywordAst _keyword;

	public:

		BreakStatementAst(KeywordAst&& keyword):
			StatementAst(StatementType::Break),
			_keyword(std::move(keyword))
		{}
		BreakStatementAst(BreakStatementAst&&) = default;
		BreakStatementAst(const BreakStatementAst&) = delete;

		const Snippet& snippet() const { return _keyword.snippet(); }
		const auto& keyword() const { return _keyword; }
	};
}

#endif
