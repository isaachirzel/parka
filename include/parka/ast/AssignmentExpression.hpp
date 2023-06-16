#ifndef PARKA_SYNTAX_EXPRESSION_ASSIGNMENT_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_ASSIGNMENT_SYNTAX_HPP

#include "parka/enum/AssignmentType.hpp"
#include "parka/ast/Expression.hpp"

namespace parka
{
	class AssignmentExpressionContext : public ExpressionContext
	{
		ExpressionContext& _lhs;
		ExpressionContext& _rhs;
		AssignmentType _assignmentType;

	public:

		AssignmentExpressionContext(ExpressionContext& lhs, ExpressionContext& rhs, AssignmentType assignmentType) :
		_lhs(lhs),
		_rhs(rhs),
		_assignmentType(assignmentType)
		{}
		AssignmentExpressionContext(AssignmentExpressionContext&&) = default;
		AssignmentExpressionContext(const AssignmentExpressionContext&) = delete;

		ExpressionType expressionType() const { return ExpressionType::Assignment; }
		const ValueType& valueType() const { return ValueType::voidType; }
		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
		const auto& assignmentType() const { return _assignmentType; }
	};

	class AssignmentExpressionSyntax : public ExpressionSyntax
	{
		Snippet _snippet;
		ExpressionSyntax& _lhs;
		ExpressionSyntax& _rhs;
		AssignmentType _assignmentType;

	public:

		AssignmentExpressionSyntax(ExpressionSyntax& lhs, ExpressionSyntax& rhs, AssignmentType assignmentType) :
		_snippet(lhs.snippet() + rhs.snippet()),
		_lhs(lhs),
		_rhs(rhs),
		_assignmentType(assignmentType)
		{}
		AssignmentExpressionSyntax(AssignmentExpressionSyntax&&) = default;
		AssignmentExpressionSyntax(const AssignmentExpressionSyntax&) = delete;

		static ExpressionSyntax *parse(Token& token);
		ExpressionContext *validate(SymbolTable& symbolTable);

		ExpressionType expressionType() const { return ExpressionType::Assignment; }
		const Snippet& snippet() const { return _snippet; }
		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
		const auto& assignmentType() const { return _assignmentType; }
	};
}

#endif
