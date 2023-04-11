#ifndef PARKA_SYNTAX_EXPRESSION_BOOLEAN_AND_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_BOOLEAN_AND_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"

namespace parka
{
	class BooleanAndExpressionSyntax : public ExpressionSyntax
	{
		ExpressionId _lhs;
		ExpressionId _rhs;

		BooleanAndExpressionSyntax(ExpressionId&& lhs, ExpressionId&& rhs) :
		_lhs(std::move(lhs)),
		_rhs(std::move(rhs))
		{}

	public:

		BooleanAndExpressionSyntax(BooleanAndExpressionSyntax&&) = default;
		BooleanAndExpressionSyntax(const BooleanAndExpressionSyntax&) = delete;
		~BooleanAndExpressionSyntax() = default;

		static Optional<ExpressionId> parse(Token& token);

		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
	};
}

#endif
