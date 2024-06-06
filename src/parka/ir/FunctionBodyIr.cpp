#include "parka/ir/FunctionBodyIr.hpp"
#include "parka/enum/FunctionBodyType.hpp"

namespace parka::ir
{
	FunctionBodyIr::FunctionBodyIr(FunctionBodyType functionBodyType):
		_functionBodyType(functionBodyType)
	{}

	FunctionBodyIr::FunctionBodyIr(ExpressionIr& expression):
		_expression(&expression),
		_functionBodyType(FunctionBodyType::Expression)
	{}

	FunctionBodyIr::FunctionBodyIr(BlockStatementIr& blockStatement):
		_blockStatement(&blockStatement),
		_functionBodyType(FunctionBodyType::Block)
	{}

	FunctionBodyIr FunctionBodyIr::notImplemented()
	{
		return FunctionBodyIr(FunctionBodyType::NotImplemented);
	}

	FunctionBodyIr FunctionBodyIr::intrinsic()
	{
		return FunctionBodyIr(FunctionBodyType::Intrinsic);
	}

	FunctionBodyIr& FunctionBodyIr::operator=(FunctionBodyIr&& other)
	{
		_functionBodyType = other._functionBodyType;

		switch (_functionBodyType)
		{
			case FunctionBodyType::Block:
				_blockStatement = other._blockStatement;
				break;

			case FunctionBodyType::Expression:
				_expression = other._expression;
				break;

			case FunctionBodyType::Intrinsic:
			case FunctionBodyType::NotImplemented:
				break;
		}

		return *this;
	}
}
