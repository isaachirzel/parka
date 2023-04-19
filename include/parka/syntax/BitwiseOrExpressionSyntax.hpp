#ifndef PARKA_SYNTAX_EXPRESSION_BITWISE_OR_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_BITWISE_OR_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"

namespace parka
{
	class BitwiseOrExpressionSyntax : public ExpressionSyntax
	{
		ExpressionSyntaxId _lhs;
		ExpressionSyntaxId _rhs;

		BitwiseOrExpressionSyntax(ExpressionSyntaxId&& lhs, ExpressionSyntaxId&&rhs) :
		_lhs(std::move(lhs)),
		_rhs(std::move(rhs))
		{}

	public:

		BitwiseOrExpressionSyntax(BitwiseOrExpressionSyntax&&) = default;
		BitwiseOrExpressionSyntax(const BitwiseOrExpressionSyntax&) = delete;

		static Optional<ExpressionSyntaxId> parse(Token& token);

		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
	};
}

#endif
