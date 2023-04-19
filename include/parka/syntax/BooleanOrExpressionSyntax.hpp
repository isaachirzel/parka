#ifndef PARKA_SYNTAX_EXPRESSION_BOOLEAN_OR_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_BOOLEAN_OR_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"

namespace parka
{
	class BooleanOrExpressionSyntax : public ExpressionSyntax
	{
		ExpressionSyntaxId _lhs;
		ExpressionSyntaxId _rhs;

		BooleanOrExpressionSyntax(ExpressionSyntaxId&& lhs, ExpressionSyntaxId&&rhs) :
		_lhs(std::move(lhs)),
		_rhs(std::move(rhs))
		{}

	public:

		BooleanOrExpressionSyntax(BooleanOrExpressionSyntax&&) = default;
		BooleanOrExpressionSyntax(const BooleanOrExpressionSyntax&) = delete;

		static Optional<ExpressionSyntaxId> parse(Token& token);

		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
	};
}

#endif
