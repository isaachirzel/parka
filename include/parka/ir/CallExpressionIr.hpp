#ifndef PARKA_IR_CALL_EXPRESSION_IR_HPP
#define PARKA_IR_CALL_EXPRESSION_IR_HPP

#include "parka/enum/ExpressionType.hpp"
#include "parka/ir/ExpressionIr.hpp"
#include "parka/ir/BinaryOperatorIr.hpp"
#include "parka/util/Array.hpp"

namespace parka::ir
{
	class CallExpressionIr: public ExpressionIr
	{
		ExpressionIr& _subject;
		Array<ExpressionIr*> _arguments;
		BinaryOperatorIr& _op;

		// TODO: Make operator binary operator, i need more flexibility in the operator system

	public:

		CallExpressionIr(ExpressionIr& subject, Array<ExpressionIr*> arguments, BinaryOperatorIr& op):
			ExpressionIr(ExpressionType::Call),
			_subject(subject),
			_arguments(std::move(arguments)),
			_op(op)
		{}
		CallExpressionIr(CallExpressionIr&&) = default;
		CallExpressionIr(const CallExpressionIr&) = delete;

		const auto& subject() const { return _subject; }
		const auto& arguments() const { return _arguments; }
		const auto& op() const { return _op; }
		const Type& type() const { return _op.returnType(); }
	};
}

#endif
