#ifndef PARKA_SYNTAX_EXPRESSION_BITWISE_OR_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_BITWISE_OR_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"

namespace parka
{
	class BitwiseOrExpressionSyntax : public ExpressionSyntax
	{
		const ExpressionSyntax& _lhs;
		const ExpressionSyntax& _rhs;

		BitwiseOrExpressionSyntax(const ExpressionSyntax& lhs, const ExpressionSyntax& rhs) :
		_lhs(lhs),
		_rhs(rhs)
		{}

	public:

		BitwiseOrExpressionSyntax(BitwiseOrExpressionSyntax&&) = default;
		BitwiseOrExpressionSyntax(const BitwiseOrExpressionSyntax&) = delete;

		static const ExpressionSyntax *parse(Token& token);

		ExpressionType expressionType() const { return ExpressionType::BitwiseOr; }
		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
	};
}

#endif
