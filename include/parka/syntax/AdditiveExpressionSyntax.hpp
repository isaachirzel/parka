#ifndef PARKA_SYNTAX_ADDITIVE_EXPRESSION_SYNTAX_HPP
#define PARKA_SYNTAX_ADDITIVE_EXPRESSION_SYNTAX_HPP

#include "parka/context/ExpressionContext.hpp"
#include "parka/enum/AdditiveType.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"

namespace parka
{
	class AdditiveExpressionSyntax : public ExpressionSyntax
	{
		ExpressionSyntax& _lhs;
		ExpressionSyntax& _rhs;
		AdditiveType _type;
		
	public:

		AdditiveExpressionSyntax(ExpressionSyntax& lhs, ExpressionSyntax& rhs, AdditiveType type) :
		_lhs(lhs),
		_rhs(rhs),
		_type(type)
		{}
		AdditiveExpressionSyntax(AdditiveExpressionSyntax&&) = default;
		AdditiveExpressionSyntax(AdditiveExpressionSyntax&) = delete;

		static ExpressionSyntax *parse(Token& token);

		ExpressionContext *validate() const;

		ExpressionType expressionType() const { return ExpressionType::Additive; }
		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
		const auto& type() const { return _type; }
	};
}

#endif
