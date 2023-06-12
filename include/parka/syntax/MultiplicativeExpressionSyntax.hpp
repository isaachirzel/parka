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
		ExpressionSyntax& _lhs;
		ExpressionSyntax& _rhs;
		MultiplicativeType _type;

	public:

		MultiplicativeExpressionSyntax(ExpressionSyntax& lhs, ExpressionSyntax& rhs, MultiplicativeType type) :
		_lhs(lhs),
		_rhs(rhs),
		_type(type)
		{}
		MultiplicativeExpressionSyntax(MultiplicativeExpressionSyntax&&) = default;
		MultiplicativeExpressionSyntax(const MultiplicativeExpressionSyntax&) = delete;

		static ExpressionSyntax *parse(Token& token);
		ExpressionContext *validate(SymbolTable&);

		ExpressionType expressionType() const { return ExpressionType::Multiplicative; }
		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
		const auto& type() const { return _type; }
	};
}

#endif
