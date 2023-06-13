#include "parka/context/BlockExpressionContext.hpp"

namespace parka
{
	BlockExpressionContext::BlockExpressionContext(Array<StatementContext*>&& statements) :
	_statements(std::move(statements))
	{}
}