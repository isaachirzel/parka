#ifndef PARKA_SYNTAX_EXPRESSION_ASSIGNMENT_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_ASSIGNMENT_SYNTAX_HPP

#include "parka/enum/AssignmentType.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"

namespace parka
{
	class AssignmentExpressionSyntax : public ExpressionSyntax
	{
		ExpressionSyntax& _lhs;
		ExpressionSyntax& _rhs;
		AssignmentType _assignmentType;

	public:

		AssignmentExpressionSyntax(ExpressionSyntax& lhs, ExpressionSyntax& rhs, AssignmentType assignmentType);
		AssignmentExpressionSyntax(AssignmentExpressionSyntax&&) = default;
		AssignmentExpressionSyntax(const AssignmentExpressionSyntax&) = delete;

		static ExpressionSyntax *parse(Token& token);
		ExpressionContext *validate(SymbolTable& symbolTable);

		ExpressionType expressionType() const { return ExpressionType::Assignment; }
		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
		const auto& assignmentType() const { return _assignmentType; }
	};
}

#endif
