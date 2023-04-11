#ifndef PARKA_SYNTAX_EXPRESSION_BOOLEAN_OR_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_BOOLEAN_OR_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"

namespace parka
{
	class BooleanOrExpressionSyntax : public ExpressionSyntax
	{
		ExpressionId _lhs;
		ExpressionId _rhs;

		BooleanOrExpressionSyntax(ExpressionId&& lhs, ExpressionId&&rhs) :
		_lhs(std::move(lhs)),
		_rhs(std::move(rhs))
		{}

	public:

		BooleanOrExpressionSyntax(BooleanOrExpressionSyntax&&) = default;
		BooleanOrExpressionSyntax(const BooleanOrExpressionSyntax&) = delete;
		~BooleanOrExpressionSyntax() = default;

		static Optional<ExpressionId> parse(Token& token);

		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
	};
}

#endif
