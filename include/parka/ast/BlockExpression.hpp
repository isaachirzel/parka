#ifndef PARKA_AST_BLOCK_HPP
#define PARKA_AST_BLOCK_HPP

#include "parka/ast/Expression.hpp"
#include "parka/ast/Statement.hpp"
#include "parka/enum/SymbolTableType.hpp"
#include <exception>

// TODO: Make block a statement

namespace parka::ast
{
	class BlockExpressionAst: public ExpressionAst
	{
		Snippet _snippet;
		Array<StatementAst*> _statements;

	public:

		BlockExpressionAst(const Snippet& snippet, Array<StatementAst*>&& statements):
		ExpressionAst(ExpressionType::Block),
		_snippet(snippet),
		_statements(std::move(statements))
		{}
		BlockExpressionAst(BlockExpressionAst&&) = default;
		BlockExpressionAst(const BlockExpressionAst&) = delete;

		const Snippet &snippet() const { return _snippet; }
		const auto& statements() const { return _statements; }
	};
}

#endif
