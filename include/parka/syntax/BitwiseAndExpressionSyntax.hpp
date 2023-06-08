#ifndef PARKA_SYNTAX_EXPRESSION_BITWISE_AND_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_BITWISE_AND_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"

namespace parka
{
	class BitwiseAndExpressionSyntax : public ExpressionSyntax
	{
		const ExpressionSyntax& _lhs;
		const ExpressionSyntax& _rhs;

		BitwiseAndExpressionSyntax(const ExpressionSyntax& lhs, const ExpressionSyntax& rhs) :
		_lhs(lhs),
		_rhs(rhs)
		{}

	public:

		BitwiseAndExpressionSyntax(BitwiseAndExpressionSyntax&&) = default;
		BitwiseAndExpressionSyntax(const BitwiseAndExpressionSyntax&) = delete;

		static const ExpressionSyntax *parse(Token& token);

		ExpressionType expressionType() const { return ExpressionType::BitwiseAnd; }
		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
	};
}

#endif
