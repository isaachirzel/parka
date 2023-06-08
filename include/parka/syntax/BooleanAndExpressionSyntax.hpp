#ifndef PARKA_SYNTAX_EXPRESSION_BOOLEAN_AND_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_BOOLEAN_AND_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"

namespace parka
{
	class BooleanAndExpressionSyntax : public ExpressionSyntax
	{
		const ExpressionSyntax& _lhs;
		const ExpressionSyntax& _rhs;

		BooleanAndExpressionSyntax(const ExpressionSyntax& lhs, const ExpressionSyntax& rhs) :
		_lhs(lhs),
		_rhs(rhs)
		{}

	public:

		BooleanAndExpressionSyntax(BooleanAndExpressionSyntax&&) = default;
		BooleanAndExpressionSyntax(const BooleanAndExpressionSyntax&) = delete;
		
		static const ExpressionSyntax *parse(Token& token);

		ExpressionType expressionType() const { return ExpressionType::BooleanAnd; }
		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
	};
}

#endif
