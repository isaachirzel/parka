#include "parka/ir/FunctionBodyIr.hpp"

namespace parka::ir
{
	FunctionBodyIr::FunctionBodyIr(ExpressionIr& expression):
		_expression(&expression),
		_isExpression(true)
	{}

	FunctionBodyIr::FunctionBodyIr(BlockStatementIr& blockStatement):
		_blockStatement(&blockStatement),
		_isExpression(false)
	{}
}
