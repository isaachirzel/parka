#ifndef PARKA_SYNTAX_ADDITIVE_EXPRESSION_SYNTAX_HPP
#define PARKA_SYNTAX_ADDITIVE_EXPRESSION_SYNTAX_HPP

#include "parka/enum/AdditiveType.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"

#include <utility>

namespace parka
{
	class AdditiveExpressionSyntax : public ExpressionSyntax
	{
		const ExpressionSyntax& _lhs;
		const ExpressionSyntax& _rhs;
		const AdditiveType _type;

		AdditiveExpressionSyntax(const ExpressionSyntax& lhs, const ExpressionSyntax& rhs, AdditiveType type) :
		_lhs(lhs),
		_rhs(rhs),
		_type(type)
		{}
		
	public:

		AdditiveExpressionSyntax(AdditiveExpressionSyntax&&) = default;
		AdditiveExpressionSyntax(const AdditiveExpressionSyntax&) = delete;

		static const ExpressionSyntax *parse(Token& token);

		ExpressionType expressionType() const { return ExpressionType::Additive; }
		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
		const auto& type() const { return _type; }
	};
}

#endif
