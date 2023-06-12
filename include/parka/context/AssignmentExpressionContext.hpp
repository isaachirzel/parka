#ifndef PARKA_CONTEXT_ASSIGNMENT_EXPRESSION_CONTEXT_HPP
#define PARKA_CONTEXT_ASSIGNMENT_EXPRESSION_CONTEXT_HPP

#include "parka/context/ExpressionContext.hpp"
#include "parka/enum/AssignmentType.hpp"

namespace parka
{
	class AssignmentExpressionContext : public ExpressionContext
	{
		ExpressionContext& _lhs;
		ExpressionContext& _rhs;
		AssignmentType _type;

	public:

		AssignmentExpressionContext(ExpressionContext& lhs, ExpressionContext& rhs, AssignmentType type);
		AssignmentExpressionContext(AssignmentExpressionContext&&) = default;
		AssignmentExpressionContext(const AssignmentExpressionContext&) = delete;

		ExpressionType expressionType() const { return ExpressionType::Assignment; }
		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
		const auto& type() const { return _type; }
	};
}

#endif
