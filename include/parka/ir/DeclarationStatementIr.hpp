#ifndef PARKA_IR_DECLARATION_STATEMENT_HPP
#define PARKA_IR_DECLARATION_STATEMENT_HPP

#include "parka/ir/ConversionIr.hpp"
#include "parka/ir/ExpressionIr.hpp"
#include "parka/ir/StatementIr.hpp"
#include "parka/ir/VariableIr.hpp"

namespace parka::ir
{
	class DeclarationStatementIr: public StatementIr
	{
		VariableIr& _variable;
		ExpressionIr& _value;

	public:

		DeclarationStatementIr(VariableIr& variable, ExpressionIr& value):
			StatementIr(StatementType::Declaration),
			_variable(variable),
			_value(value)
		{}
		DeclarationStatementIr(DeclarationStatementIr&&) = default;
		DeclarationStatementIr(const DeclarationStatementIr&) = delete;

		const auto& variable() const { return _variable; }
		const auto& value() const { return _value; }
	};
}

#endif
