#ifndef PARKA_SYNTAX_EXPRESSION_BOOLEAN_AND_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_BOOLEAN_AND_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"

namespace parka
{
	class BooleanAndExpressionSyntax : public ExpressionSyntax
	{
		ExpressionSyntaxId _lhs;
		ExpressionSyntaxId _rhs;

		BooleanAndExpressionSyntax(ExpressionSyntaxId&& lhs, ExpressionSyntaxId&& rhs) :
		_lhs(std::move(lhs)),
		_rhs(std::move(rhs))
		{}

	public:

		BooleanAndExpressionSyntax(BooleanAndExpressionSyntax&&) = default;
		BooleanAndExpressionSyntax(const BooleanAndExpressionSyntax&) = delete;
		~BooleanAndExpressionSyntax() = default;

		static Optional<ExpressionSyntaxId> parse(Token& token);

		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
	};
}

#endif
