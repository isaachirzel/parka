#ifndef PARKA_IR_ASSIGNMENT_STATEMENT_IR_HPP
#define PARKA_IR_ASSIGNMENT_STATEMENT_IR_HPP

#include "parka/enum/AssignmentType.hpp"
#include "parka/ir/ConversionIr.hpp"
#include "parka/ir/ExpressionIr.hpp"
#include "parka/ir/IdentifierExpressionIr.hpp"
#include "parka/ir/StatementIr.hpp"

namespace parka::ir
{
	class AssignmentStatementIr: public StatementIr
	{
		IdentifierExpressionIr& _identifier;
		ExpressionIr& _value;
		ConversionIr& _conversion;
		AssignmentType _assignmentType;

	public:

		AssignmentStatementIr(IdentifierExpressionIr& identifier, ExpressionIr& value, ConversionIr& conversion, AssignmentType assignmentType):
			StatementIr(StatementType::Assignment),
			_identifier(identifier),
			_value(value),
			_conversion(conversion),
			_assignmentType(assignmentType)
		{}
		AssignmentStatementIr(AssignmentStatementIr&&) = default;
		AssignmentStatementIr(const AssignmentStatementIr&) = delete;

		const auto& identifier() const { return _identifier; }
		const auto& value() const { return _value; }
		const auto& conversion() const { return _conversion; }
		const auto& assignmentType() const { return _assignmentType; }
	};
}

#endif
