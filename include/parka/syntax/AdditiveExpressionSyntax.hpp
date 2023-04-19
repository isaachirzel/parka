#ifndef PARKA_SYNTAX_ADDITIVE_EXPRESSION_SYNTAX_HPP
#define PARKA_SYNTAX_ADDITIVE_EXPRESSION_SYNTAX_HPP

#include "parka/enum/AdditiveType.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"

#include <utility>

namespace parka
{
	class AdditiveExpressionSyntax : public ExpressionSyntax
	{
		ExpressionSyntaxId _lhs;
		ExpressionSyntaxId _rhs;
		AdditiveType _type;

		AdditiveExpressionSyntax(ExpressionSyntaxId&& lhs, ExpressionSyntaxId&& rhs, AdditiveType type) :
		_lhs(std::move(lhs)),
		_rhs(std::move(rhs)),
		_type(type)
		{}
		
	public:

		AdditiveExpressionSyntax(AdditiveExpressionSyntax&&) = default;
		AdditiveExpressionSyntax(const AdditiveExpressionSyntax&) = delete;

		static Optional<ExpressionSyntaxId> parse(Token& token);

		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
		const auto& type() const { return _type; }
	};
}

#endif
