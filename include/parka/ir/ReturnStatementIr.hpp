#ifndef PARKA_IR_RETURN_STATEMENT_HPP
#define PARKA_IR_RETURN_STATEMENT_HPP

#include "parka/ir/ExpressionIr.hpp"
#include "parka/ir/StatementIr.hpp"

namespace parka::ir
{
	class ReturnStatementIr: public StatementIr
	{
		ExpressionIr* _value;

	public:

		ReturnStatementIr():
			StatementIr(StatementType::Return),
			_value(nullptr)
		{}
		ReturnStatementIr(ExpressionIr& value):
			StatementIr(StatementType::Return),
			_value(&value)
		{}
		ReturnStatementIr(ReturnStatementIr&&) = default;
		ReturnStatementIr(const ReturnStatementIr&) = delete;

		bool hasValue() const { return !!_value; }
		const ExpressionIr& value() const { assert(_value); return *_value; }
	};
}

#endif
