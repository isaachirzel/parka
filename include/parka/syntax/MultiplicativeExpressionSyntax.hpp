#ifndef PARKA_SYNTAX_EXPRESSION_MULTIPLICATIVE_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_MULTIPLICATIVE_SYNTAX_HPP

#include "parka/enum/MultiplicativeType.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/util/Optional.hpp"

#include <utility>

namespace parka
{
	class MultiplicativeExpressionSyntax : public ExpressionSyntax
	{
		const ExpressionSyntax& _lhs;
		const ExpressionSyntax& _rhs;
		MultiplicativeType _type;

		MultiplicativeExpressionSyntax(const ExpressionSyntax& lhs, const ExpressionSyntax& rhs, MultiplicativeType type) :
		_lhs(lhs),
		_rhs(rhs),
		_type(type)
		{}

	public:

		MultiplicativeExpressionSyntax(MultiplicativeExpressionSyntax&&) = default;
		MultiplicativeExpressionSyntax(const MultiplicativeExpressionSyntax&) = delete;

		static const ExpressionSyntax *parse(Token& token);

		ExpressionType expressionType() const { return ExpressionType::Multiplicative; }
		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
		const auto& type() const { return _type; }
	};
}

#endif
