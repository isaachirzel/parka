#ifndef PARKA_IR_RETURN_STATEMENT_HPP
#define PARKA_IR_RETURN_STATEMENT_HPP

#include "parka/ir/ExpressionIr.hpp"
#include "parka/ir/StatementIr.hpp"

namespace parka::ir
{
	class ReturnStatementIr: public StatementIr
	{
		ExpressionIr *_value;

	public:

		ReturnStatementIr(ExpressionIr *value):
			StatementIr(StatementType::Return),
			_value(value)
		{}

		bool hasValue() const { return !!_value; }
		const ExpressionIr& value() const { assert(_value); return *_value; }
	};
}

#endif
