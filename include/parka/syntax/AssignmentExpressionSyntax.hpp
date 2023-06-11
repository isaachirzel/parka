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
		AssignmentType _type;

	public:

		AssignmentExpressionSyntax(ExpressionSyntax& lhs, ExpressionSyntax& rhs, AssignmentType type) :
		_lhs(lhs),
		_rhs(rhs),
		_type(type)
		{}
		AssignmentExpressionSyntax(AssignmentExpressionSyntax&&) = default;
		AssignmentExpressionSyntax(const AssignmentExpressionSyntax&) = delete;

		static ExpressionSyntax *parse(Token& token);
		ExpressionContext *validate(SymbolTable& symbolTable) const;

		ExpressionType expressionType() const { return ExpressionType::Assignment; }
		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
		const auto& type() const { return _type; }
	};
}

#endif
