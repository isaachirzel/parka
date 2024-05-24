#ifndef PARKA_IR_ASSIGNMENT_STATEMENT_IR_HPP
#define PARKA_IR_ASSIGNMENT_STATEMENT_IR_HPP

#include "parka/enum/AssignmentType.hpp"
#include "parka/ir/AssignmentOperatorIr.hpp"
#include "parka/ir/ExpressionIr.hpp"
#include "parka/ir/IdentifierExpressionIr.hpp"
#include "parka/ir/StatementIr.hpp"

namespace parka::ir
{
	class AssignmentStatementIr: public StatementIr
	{
		IdentifierExpressionIr& _identifier;
		ExpressionIr& _value;
		AssignmentOperatorIr& _op;

	public:

		AssignmentStatementIr(IdentifierExpressionIr& identifier, ExpressionIr& value, AssignmentOperatorIr& op):
			StatementIr(StatementType::Assignment),
			_identifier(identifier),
			_value(value),
			_op(op)
		{}
		AssignmentStatementIr(AssignmentStatementIr&&) = default;
		AssignmentStatementIr(const AssignmentStatementIr&) = delete;

		const auto& identifier() const { return _identifier; }
		const auto& value() const { return _value; }
		const auto& op() const { return _op; }
	};
}

#endif
