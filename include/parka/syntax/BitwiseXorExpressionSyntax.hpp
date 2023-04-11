#ifndef PARKA_SYNTAX_EXPRESSION_BITWISE_XOR_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_BITWISE_XOR_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"

namespace parka
{
	class BitwiseXorExpressionSyntax : public ExpressionSyntax
	{
		ExpressionId _lhs;
		ExpressionId _rhs;

		BitwiseXorExpressionSyntax(ExpressionId&& lhs, ExpressionId&&rhs) :
		_lhs(std::move(lhs)),
		_rhs(std::move(rhs))
		{}

	public:

		BitwiseXorExpressionSyntax(BitwiseXorExpressionSyntax&&) = default;
		BitwiseXorExpressionSyntax(const BitwiseXorExpressionSyntax&) = delete;
		~BitwiseXorExpressionSyntax() = default;

		static Optional<ExpressionId> parse(Token& token);

		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
	};
}

#endif
