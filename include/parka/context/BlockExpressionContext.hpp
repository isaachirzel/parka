#ifndef PARKA_CONTEXT_BLOCK_EXPRESSION_CONTEXT_HPP
#define PARKA_CONTEXT_BLOCK_EXPRESSION_CONTEXT_HPP

#include "parka/context/ExpressionContext.hpp"
#include "parka/context/StatementContext.hpp"

namespace parka
{
	class BlockExpressionContext : public ExpressionContext
	{
		Array<StatementContext*> _statements;
		ValueType _valueType;

	public:

		BlockExpressionContext(Array<StatementContext*>&& statements, ValueType&& valueType);
		BlockExpressionContext(BlockExpressionContext&&) = default;
		BlockExpressionContext(const BlockExpressionContext&) = delete;

		const ValueType& valueType() const { return _valueType; }
		ExpressionType expressionType() const { return ExpressionType::Block; }
		const auto& statements() const { return _statements; }
	};
}

#endif
