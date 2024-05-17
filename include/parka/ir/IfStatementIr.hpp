#ifndef PARKA_IR_IF_STATEMENT_IR_HPP
#define PARKA_IR_IF_STATEMENT_IR_HPP

#include "parka/ir/ConversionIr.hpp"
#include "parka/ir/ExpressionIr.hpp"
#include "parka/ir/StatementIr.hpp"

namespace parka::ir
{
	class IfStatementIr: public StatementIr
	{
		ExpressionIr& _condition;
		ConversionIr* _conversion;
		StatementIr& _thenCase;
		StatementIr* _elseCase;

	public:

		IfStatementIr(ExpressionIr& condition, ConversionIr* conversion, StatementIr& thenCase, StatementIr* elseCase):
			StatementIr(StatementType::If),
			_condition(condition),
			_conversion(conversion),
			_thenCase(thenCase),
			_elseCase(elseCase)
		{}
		IfStatementIr(IfStatementIr&&) = default;
		IfStatementIr(const IfStatementIr&) = delete;

		const auto& condition() const { return _condition; }
		const auto* conversion() const { return _conversion; }
		const auto& thenCase() const { return _thenCase; }
		bool hasElseCase() const { return !!_elseCase; }
		const auto& elseCase() const { assert(_elseCase); return *_elseCase; }
	};
}

#endif
