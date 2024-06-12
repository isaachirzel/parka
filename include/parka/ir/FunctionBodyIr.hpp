#ifndef PARKA_IR_FUNCTION_BODY_IR_HPP
#define PARKA_IR_FUNCTION_BODY_IR_HPP

#include "parka/enum/FunctionBodyType.hpp"
#include "parka/enum/IntrinsicFunctionType.hpp"
#include "parka/ir/BlockStatementIr.hpp"
#include "parka/ir/ExpressionIr.hpp"

namespace parka::ir
{
	class FunctionBodyIr
	{
		union
		{
			ExpressionIr* _expression;
			BlockStatementIr* _blockStatement;
			IntrinsicFunctionType _intrinsicFunctionType;
		};
		FunctionBodyType _functionBodyType;

	private:

		FunctionBodyIr(FunctionBodyType functionBodyType);

	public:

		FunctionBodyIr();
		FunctionBodyIr(IntrinsicFunctionType intrinsicFunctionType);
		FunctionBodyIr(ExpressionIr& expression);
		FunctionBodyIr(BlockStatementIr& blockStatement);
		FunctionBodyIr(FunctionBodyIr&&) = default;
		FunctionBodyIr(const FunctionBodyIr&) = delete;
		~FunctionBodyIr() = default;

		FunctionBodyIr& operator=(FunctionBodyIr&& other);

		const auto& expression() const { assert(_functionBodyType == FunctionBodyType::Expression); return *_expression; }
		const auto& blockStatement() const { assert(_functionBodyType == FunctionBodyType::Block); return *_blockStatement; }
		const auto& intrinsicFunctionType() const { assert(_functionBodyType == FunctionBodyType::Intrinsic); return _intrinsicFunctionType; }
		const auto& functionBodyType() const { return _functionBodyType; }
	};
}

#endif
