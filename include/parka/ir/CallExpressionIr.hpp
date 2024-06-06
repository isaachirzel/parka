#ifndef PARKA_IR_CALL_EXPRESSION_IR_HPP
#define PARKA_IR_CALL_EXPRESSION_IR_HPP

#include "parka/enum/ExpressionType.hpp"
#include "parka/ir/CallOperatorIr.hpp"
#include "parka/ir/ExpressionIr.hpp"
#include "parka/ir/FunctionIr.hpp"
#include "parka/ir/PrototypeIr.hpp"
#include "parka/util/Array.hpp"

namespace parka::ir
{
	class CallExpressionIr: public ExpressionIr
	{
		const FunctionIr& _subject;
		Array<ExpressionIr*> _arguments;

		// TODO: Make operator binary operator, i need more flexibility in the operator system

	public:

		CallExpressionIr(const FunctionIr& subject, Array<ExpressionIr*>&& arguments):
			ExpressionIr(ExpressionType::Call),
			_subject(subject),
			_arguments(std::move(arguments))
		{}
		CallExpressionIr(CallExpressionIr&&) = default;
		CallExpressionIr(const CallExpressionIr&) = delete;

		const auto& subject() const { return _subject; }
		const auto& arguments() const { return _arguments; }
		const TypeIr& type() const { return _subject.prototype().returnType(); }
	};
}

#endif
