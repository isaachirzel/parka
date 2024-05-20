#ifndef PARKA_IR_FUNCTION_BODY_IR_HPP
#define PARKA_IR_FUNCTION_BODY_IR_HPP

#include "parka/ir/BlockStatementIr.hpp"
#include "parka/ir/ConversionIr.hpp"
#include "parka/ir/ExpressionIr.hpp"

namespace parka::ir
{
	class FunctionBodyIr
	{
		struct ExpressionBody
		{
			ExpressionIr& _expression;
			ConversionIr* _conversion;
		};

		union
		{
			ExpressionBody _expression;
			BlockStatementIr* _blockStatement;
		};
		bool _isExpression;

	public:

		FunctionBodyIr(ExpressionIr& expression, ConversionIr* conversion);
		FunctionBodyIr(BlockStatementIr& blockStatement);
		FunctionBodyIr(FunctionBodyIr&&) = default;
		FunctionBodyIr(const FunctionBodyIr&) = delete;
		~FunctionBodyIr() = default;

		const auto& expression() const { assert(_isExpression); return _expression; }
		const auto& blockStatement() const { assert(_isExpression); return *_blockStatement; }
		const auto& isExpression() const { return _isExpression; }
	};
}

#endif
