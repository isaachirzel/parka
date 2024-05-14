#ifndef PARKA_IR_FOR_STATEMENT_IR_HPP
#define PARKA_IR_FOR_STATEMENT_IR_HPP

#include "parka/ir/BlockStatementIr.hpp"
#include "parka/ir/ConversionIr.hpp"
#include "parka/ir/DeclarationStatementIr.hpp"
#include "parka/ir/ExpressionIr.hpp"
#include "parka/ir/StatementIr.hpp"

namespace parka::ir
{
	class ForStatementIr: public StatementIr
	{
		DeclarationStatementIr& _declaration;
		ExpressionIr& _condition;
		ConversionIr* _conversion;
		StatementIr& _action;
		BlockStatementIr& _body;

	public:

		ForStatementIr(DeclarationStatementIr& declaration, ExpressionIr& condition, ConversionIr* conversion, StatementIr& action, BlockStatementIr& body):
			StatementIr(StatementType::For),
			_declaration(declaration),
			_condition(condition),
			_conversion(conversion),
			_action(action),
			_body(body)
		{}
		ForStatementIr(ForStatementIr&&) = default;
		ForStatementIr(const ForStatementIr&) = delete;

		const auto& declaration() const { return _declaration; }
		const auto& condition() const { return _condition; }
		const auto* conversion() const { return _conversion; }
		const auto& action() const { return _action; }
		const auto& body() const { return _body; }
	};
}

#endif
