#ifndef PARKA_CONTEXT_BLOCK_EXPRESSION_CONTEXT_HPP
#define PARKA_CONTEXT_BLOCK_EXPRESSION_CONTEXT_HPP

#include "parka/context/ExpressionContext.hpp"
#include "parka/context/StatementContext.hpp"

namespace parka
{
	class BlockExpressionContext : public ExpressionContext
	{
		Array<StatementContext*> _statements;

	public:

		BlockExpressionContext(Array<StatementContext*>&& statements);
		BlockExpressionContext(BlockExpressionContext&&) = default;
		BlockExpressionContext(const BlockExpressionContext&) = delete;

		ExpressionType expressionType() const { return ExpressionType::Block; }
		const auto& statements() const { return _statements; }
	};
}

#endif
