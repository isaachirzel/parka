#ifndef PARKA_SYNTAX_EXPRESSION_EQUALITY_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_EQUALITY_SYNTAX_HPP

#include "parka/enum/EqualityType.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"

namespace parka
{
	class EqualityExpressionSyntax : public ExpressionSyntax
	{
		const ExpressionSyntax& _lhs;
		const ExpressionSyntax& _rhs;
		EqualityType _type;

		EqualityExpressionSyntax(const ExpressionSyntax& lhs, const ExpressionSyntax& rhs, EqualityType type) :
		_lhs(lhs),
		_rhs(rhs),
		_type(type)
		{}

	public:

		EqualityExpressionSyntax(EqualityExpressionSyntax&&) = default;
		EqualityExpressionSyntax(const EqualityExpressionSyntax&) = delete;

		static const ExpressionSyntax *parse(Token& token);

		ExpressionType expressionType() const { return ExpressionType::Equality; }
		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
		const auto& type() const { return _type; }
	};
}

#endif
