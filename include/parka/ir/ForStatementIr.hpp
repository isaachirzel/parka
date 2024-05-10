#ifndef PARKA_IR_FOR_STATEMENT_IR_HPP
#define PARKA_IR_FOR_STATEMENT_IR_HPP

#include "parka/ir/DeclarationStatementIr.hpp"
#include "parka/ir/ExpressionIr.hpp"
#include "parka/ir/StatementIr.hpp"
#include "parka/ir/VariableIr.hpp"

namespace parka::ir
{
	class ForStatementIr: public StatementIr
	{
		DeclarationStatementIr& _declaration;
		ExpressionIr& _condition;
		ExpressionIr& _action;
		ExpressionIr& _body;

	public:

		ForStatementIr(DeclarationStatementIr& declaration, ExpressionIr& condition, ExpressionIr& action, ExpressionIr& body):
			StatementIr(StatementType::For),
			_declaration(declaration),
			_condition(condition),
			_action(action),
			_body(body)
		{}
		ForStatementIr(ForStatementIr&&) = default;
		ForStatementIr(const ForStatementIr&) = delete;

		const auto& declaration() const { return _declaration; }
		const auto& condition() const { return _condition; }
		const auto& action() const { return _action; }
		const auto& body() const { return _body; }
	};
}

#endif
