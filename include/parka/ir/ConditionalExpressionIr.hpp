#ifndef PARKA_IR_CONDITIONAL_EXPRESSION_IR_HPP
#define PARKA_IR_CONDITIONAL_EXPRESSION_IR_HPP

#include "parka/ir/ExpressionIr.hpp"

namespace parka::ir
{
	class ConditionalExpressionIr: public ir::ExpressionIr
	{
		ExpressionIr& _condition;
		ExpressionIr& _thenCase;
		ExpressionIr& _elseCase;

	public:

		ConditionalExpressionIr(ExpressionIr& condition, ExpressionIr& thenCase, ExpressionIr& elseCase):
			ir::ExpressionIr(ExpressionType::Conditional),
			_condition(condition),
			_thenCase(thenCase),
			_elseCase(elseCase)
		{}
		ConditionalExpressionIr(ConditionalExpressionIr&&) = default;
		ConditionalExpressionIr(const ConditionalExpressionIr&) = delete;

		const TypeIr& type() const { return _thenCase.type(); }
		const auto& condition() const { return _condition; }
		const auto& thenCase() const { return _thenCase; }
		const auto& elseCase() const { return _elseCase; }
	};
}

#endif
