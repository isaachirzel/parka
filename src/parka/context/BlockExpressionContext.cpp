#include "parka/context/BlockExpressionContext.hpp"

namespace parka
{
	BlockExpressionContext::BlockExpressionContext(Array<StatementContext*>&& statements, ValueType&& valueType) :
	_statements(std::move(statements)),
	_valueType(std::move(valueType))
	{}
}