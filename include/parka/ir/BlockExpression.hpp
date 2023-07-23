#ifndef PARKA_IR_BLOCK_EXPRESSION_HPP
#define PARKA_IR_BLOCK_EXPRESSION_HPP

#include "parka/ir/Expression.hpp"
#include "parka/ir/Statement.hpp"
#include "parka/util/Array.hpp"

namespace parka::ir
{
	class BlockExpressionIr: public ExpressionIr
	{
		Array<StatementIr*> _statements;
		Type _type;

	public:

		BlockExpressionIr(Array<StatementIr*>&& statements, Type&& Type):
		ExpressionIr(ExpressionType::Block),
		_statements(std::move(statements)),
		_type(std::move(Type))
		{}
		BlockExpressionIr(BlockExpressionIr&&) = default;
		BlockExpressionIr(const BlockExpressionIr&) = delete;
		const Type& type() const { return _type; }
		const auto& statements() const { return _statements; }
	};
}

#endif
