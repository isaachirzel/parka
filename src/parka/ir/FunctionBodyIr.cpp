#include "parka/ir/FunctionBodyIr.hpp"
#include "parka/enum/FunctionBodyType.hpp"
#include "parka/enum/IntrinsicFunctionType.hpp"

namespace parka::ir
{
	FunctionBodyIr::FunctionBodyIr():
		_functionBodyType(FunctionBodyType::NotImplemented)
	{}

	FunctionBodyIr::FunctionBodyIr(IntrinsicFunctionType intrinsicFunctionType):
		_intrinsicFunctionType(intrinsicFunctionType),
		_functionBodyType(FunctionBodyType::Intrinsic)
	{}

	FunctionBodyIr::FunctionBodyIr(ExpressionIr& expression):
		_expression(&expression),
		_functionBodyType(FunctionBodyType::Expression)
	{}

	FunctionBodyIr::FunctionBodyIr(BlockStatementIr& blockStatement):
		_blockStatement(&blockStatement),
		_functionBodyType(FunctionBodyType::Block)
	{}

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
