#ifndef PARKA_IR_RETURN_STATEMENT_HPP
#define PARKA_IR_RETURN_STATEMENT_HPP

#include "parka/ir/ConversionIr.hpp"
#include "parka/ir/ExpressionIr.hpp"
#include "parka/ir/StatementIr.hpp"

namespace parka::ir
{
	class ReturnStatementIr: public StatementIr
	{
		ExpressionIr* _value;
		ConversionIr* _conversion;

	public:

		ReturnStatementIr():
			StatementIr(StatementType::Return),
			_value(nullptr),
			_conversion(nullptr)
		{}
		ReturnStatementIr(ExpressionIr& value, ConversionIr& conversion):
			StatementIr(StatementType::Return),
			_value(&value),
			_conversion(&conversion)
		{}
		ReturnStatementIr(ReturnStatementIr&&) = default;
		ReturnStatementIr(const ReturnStatementIr&) = delete;

		bool hasValue() const { return !!_value; }
		const ExpressionIr& value() const { assert(_value); return *_value; }
		const ConversionIr& conversion() const { assert(_conversion); return *_conversion; }
	};
}

#endif
