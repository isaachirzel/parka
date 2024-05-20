#include "parka/ir/FunctionBodyIr.hpp"

namespace parka::ir
{
	FunctionBodyIr::FunctionBodyIr(ExpressionIr& expression, ConversionIr* conversion):
		_expression({ expression, conversion }),
		_isExpression(true)
	{}

	FunctionBodyIr::FunctionBodyIr(BlockStatementIr& blockStatement):
		_blockStatement(&blockStatement),
		_isExpression(false)
	{}
}
