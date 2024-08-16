#ifndef PARKA_AST_BLOCK_STATEMENT_AST_HPP
#define PARKA_AST_BLOCK_STATEMENT_AST_HPP

#include "parka/ast/StatementAst.hpp"
#include "parka/util/Array.hpp"

namespace parka::ast
{
	class BlockStatementAst: public StatementAst
	{
		fs::FileSnippet _snippet;
		Array<StatementAst*> _statements;

	public:

		BlockStatementAst(const fs::FileSnippet& snippet, Array<StatementAst*>&& statements):
			StatementAst(StatementType::Block),
			_snippet(snippet),
			_statements(std::move(statements))
		{}
		BlockStatementAst(BlockStatementAst&&) = default;
		BlockStatementAst(const BlockStatementAst&) = delete;

		const fs::FileSnippet &snippet() const { return _snippet; }
		const auto& statements() const { return _statements; }
	};
}

#endif
