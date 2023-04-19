#ifndef PARKA_SYNTAX_EXPRESSION_EQUALITY_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_EQUALITY_SYNTAX_HPP

#include "parka/enum/EqualityType.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"

namespace parka
{
	class EqualityExpressionSyntax : public ExpressionSyntax
	{
		ExpressionSyntaxId _lhs;
		ExpressionSyntaxId _rhs;
		EqualityType _type;

		EqualityExpressionSyntax(ExpressionSyntaxId&& lhs, ExpressionSyntaxId&& rhs, EqualityType type) :
		_lhs(std::move(lhs)),
		_rhs(std::move(rhs)),
		_type(type)
		{}

	public:

		EqualityExpressionSyntax(EqualityExpressionSyntax&&) = default;
		EqualityExpressionSyntax(const EqualityExpressionSyntax&) = delete;

		static Optional<ExpressionSyntaxId> parse(Token& token);

		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
		const auto& type() const { return _type; }
	};
}

#endif
