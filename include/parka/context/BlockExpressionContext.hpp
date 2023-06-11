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

		BlockExpressionContext(Array<StatementContext*>&& statements) :
		_statements(std::move(statements))
		{}
		BlockExpressionContext(BlockExpressionContext&&) = default;
		BlockExpressionContext(const BlockExpressionContext&) = delete;

		const auto& statements() const { return _statements; }
	};
}

#endif
