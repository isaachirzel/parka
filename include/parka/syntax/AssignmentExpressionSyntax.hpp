#ifndef PARKA_SYNTAX_EXPRESSION_ASSIGNMENT_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_ASSIGNMENT_SYNTAX_HPP

#include "parka/enum/AssignmentType.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"

namespace parka
{
	class AssignmentExpressionSyntax : public ExpressionSyntax
	{
		ExpressionSyntaxId _lhs;
		ExpressionSyntaxId _rhs;
		AssignmentType _type;

		AssignmentExpressionSyntax(ExpressionSyntaxId&& lhs, ExpressionSyntaxId&& rhs, AssignmentType type) :
		_lhs(std::move(lhs)),
		_rhs(std::move(rhs)),
		_type(type)
		{}

	public:

		AssignmentExpressionSyntax(AssignmentExpressionSyntax&&) = default;
		AssignmentExpressionSyntax(const AssignmentExpressionSyntax&) = delete;
		~AssignmentExpressionSyntax() = default;

		static Optional<ExpressionSyntaxId> parse(Token& token);

		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
		const auto& type() const { return _type; }
	};
}

#endif
