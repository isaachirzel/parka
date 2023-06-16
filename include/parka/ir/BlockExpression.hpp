#ifndef PARKA_IR_BLOCK_EXPRESSION_HPP
#define PARKA_IR_BLOCK_EXPRESSION_HPP

#include "parka/ir/Expression.hpp"

namespace parka::ir
{
	class BlockExpressionIr : public ExpressionIr
	{
		Array<StatementIr*> _statements;
		ValueType _valueType;

	public:

		BlockExpressionIr(Array<StatementIr*>&& statements, ValueType&& valueType) :
		_statements(std::move(statements)),
		_valueType(std::move(valueType))
		{}
		BlockExpressionIr(BlockExpressionIr&&) = default;
		BlockExpressionIr(const BlockExpressionIr&) = delete;
		const ValueType& valueType() const { return _valueType; }
		ExpressionType expressionType() const { return ExpressionType::Block; }
		const auto& statements() const { return _statements; }
	};
};

#endif
