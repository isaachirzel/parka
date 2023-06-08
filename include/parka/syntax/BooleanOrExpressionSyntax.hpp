#ifndef PARKA_SYNTAX_EXPRESSION_BOOLEAN_OR_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_BOOLEAN_OR_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"

namespace parka
{
	class BooleanOrExpressionSyntax : public ExpressionSyntax
	{
		const ExpressionSyntax& _lhs;
		const ExpressionSyntax& _rhs;

		BooleanOrExpressionSyntax(const ExpressionSyntax& lhs, const ExpressionSyntax& rhs) :
		_lhs(lhs),
		_rhs(rhs)
		{}

	public:

		BooleanOrExpressionSyntax(BooleanOrExpressionSyntax&&) = default;
		BooleanOrExpressionSyntax(const BooleanOrExpressionSyntax&) = delete;

		static const ExpressionSyntax *parse(Token& token);

		ExpressionType expressionType() const { return ExpressionType::BooleanOr; }
		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
	};
}

#endif
