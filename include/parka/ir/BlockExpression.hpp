#ifndef PARKA_IR_BLOCK_EXPRESSION_HPP
#define PARKA_IR_BLOCK_EXPRESSION_HPP

#include "parka/ir/Expression.hpp"
#include "parka/ir/Statement.hpp"
#include "parka/util/Array.hpp"

namespace parka::ir
{
	class BlockExpressionIr : public ExpressionIr
	{
		Array<StatementIr*> _statements;
		ValueType _valueType;

	public:

		BlockExpressionIr(Array<StatementIr*>&& statements, ValueType&& valueType):
		ExpressionIr(ExpressionType::Block),
		_statements(std::move(statements)),
		_valueType(std::move(valueType))
		{}
		BlockExpressionIr(BlockExpressionIr&&) = default;
		BlockExpressionIr(const BlockExpressionIr&) = delete;
		const ValueType& valueType() const { return _valueType; }
		const auto& statements() const { return _statements; }
	};
};

#endif
