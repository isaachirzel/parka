#ifndef PARKA_IR_DECLARATION_STATEMENT_HPP
#define PARKA_IR_DECLARATION_STATEMENT_HPP

#include "parka/ast/Statement.hpp"
#include "parka/ir/Expression.hpp"
#include "parka/ir/Statement.hpp"
#include "parka/ir/Variable.hpp"

namespace parka::ir
{
	class DeclarationStatementIr : public StatementIr
	{
		VariableIr& _variable;
		ExpressionIr& _value;

	public:

		DeclarationStatementIr(VariableIr& variable, ExpressionIr& value) :
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
