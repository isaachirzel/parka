#ifndef PARKA_SYNTAX_EXPRESSION_BITWISE_XOR_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_BITWISE_XOR_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"

namespace parka
{
	class BitwiseXorExpressionSyntax : public ExpressionSyntax
	{
		ExpressionSyntax& _lhs;
		ExpressionSyntax& _rhs;

	public:

		BitwiseXorExpressionSyntax(ExpressionSyntax& lhs, ExpressionSyntax& rhs);
		BitwiseXorExpressionSyntax(BitwiseXorExpressionSyntax&&) = default;
		BitwiseXorExpressionSyntax(const BitwiseXorExpressionSyntax&) = delete;

		static ExpressionSyntax *parse(Token& token);

		ExpressionType expressionType() const { return ExpressionType::BitwiseXor; }
		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
	};
}

#endif
