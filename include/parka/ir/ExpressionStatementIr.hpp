#ifndef PARKA_IR_EXPRESSION_STATEMENT_IR_HPP
#define PARKA_IR_EXPRESSION_STATEMENT_IR_HPP

#include "parka/ir/ExpressionIr.hpp"
#include "parka/ir/StatementIr.hpp"

namespace parka::ir
{
	class ExpressionStatementIr: public StatementIr
	{
		ExpressionIr& _expression;

	public:

		ExpressionStatementIr(ExpressionIr& expression):
			StatementIr(StatementType::Expression),
			_expression(expression)
		{}
		ExpressionStatementIr(ExpressionStatementIr&&) = default;
		ExpressionStatementIr(const ExpressionStatementIr&) = delete;

		const auto& expression() const { return _expression; }
	};
}

#endif
