#ifndef PARKA_SYNTAX_EXPRESSION_BITWISE_XOR_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_BITWISE_XOR_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"

namespace parka
{
	class BitwiseXorExpressionSyntax : public ExpressionSyntax
	{
		ExpressionSyntaxId _lhs;
		ExpressionSyntaxId _rhs;

		BitwiseXorExpressionSyntax(ExpressionSyntaxId&& lhs, ExpressionSyntaxId&&rhs) :
		_lhs(std::move(lhs)),
		_rhs(std::move(rhs))
		{}

	public:

		BitwiseXorExpressionSyntax(BitwiseXorExpressionSyntax&&) = default;
		BitwiseXorExpressionSyntax(const BitwiseXorExpressionSyntax&) = delete;
		~BitwiseXorExpressionSyntax() = default;

		static Optional<ExpressionSyntaxId> parse(Token& token);

		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
	};
}

#endif
