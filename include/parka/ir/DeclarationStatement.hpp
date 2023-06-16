#ifndef PARKA_IR_DECLARATION_STATEMENT_HPP
#define PARKA_IR_DECLARATION_STATEMENT_HPP

#include "parka/ast/Statement.hpp"

namespace parka::ir
{
	class DeclarationStatementIr : public StatementIr
	{
		VariableIr& _variable;
		ExpressionIr& _value;

	public:

		DeclarationStatementIr(VariableIr& variable, ExpressionIr& value) :
		_variable(variable),
		_value(value)
		{}
		DeclarationStatementIr(DeclarationStatementIr&&) = default;
		DeclarationStatementIr(const DeclarationStatementIr&) = delete;

		StatementType statementType() const { return StatementType::Declaration; }
	};
}

#endif
