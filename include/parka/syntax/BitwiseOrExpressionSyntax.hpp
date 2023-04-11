#ifndef PARKA_SYNTAX_EXPRESSION_BITWISE_OR_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_BITWISE_OR_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"

namespace parka
{
	class BitwiseOrExpressionSyntax : public ExpressionSyntax
	{
		ExpressionId _lhs;
		ExpressionId _rhs;

		BitwiseOrExpressionSyntax(ExpressionId&& lhs, ExpressionId&&rhs) :
		_lhs(std::move(lhs)),
		_rhs(std::move(rhs))
		{}

	public:

		BitwiseOrExpressionSyntax(BitwiseOrExpressionSyntax&&) = default;
		BitwiseOrExpressionSyntax(const BitwiseOrExpressionSyntax&) = delete;
		~BitwiseOrExpressionSyntax() = default;

		static Optional<ExpressionId> parse(Token& token);

		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
	};
}

#endif
