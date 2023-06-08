#ifndef PARKA_SYNTAX_EXPRESSION_BITWISE_XOR_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_BITWISE_XOR_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"

namespace parka
{
	class BitwiseXorExpressionSyntax : public ExpressionSyntax
	{
		const ExpressionSyntax& _lhs;
		const ExpressionSyntax& _rhs;

		BitwiseXorExpressionSyntax(const ExpressionSyntax& lhs, const ExpressionSyntax& rhs) :
		_lhs(lhs),
		_rhs(rhs)
		{}

	public:

		BitwiseXorExpressionSyntax(BitwiseXorExpressionSyntax&&) = default;
		BitwiseXorExpressionSyntax(const BitwiseXorExpressionSyntax&) = delete;

		static const ExpressionSyntax *parse(Token& token);

		ExpressionType expressionType() const { return ExpressionType::BitwiseXor; }
		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
	};
}

#endif
