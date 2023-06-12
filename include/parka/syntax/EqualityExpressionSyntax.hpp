#ifndef PARKA_SYNTAX_EXPRESSION_EQUALITY_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_EQUALITY_SYNTAX_HPP

#include "parka/enum/EqualityType.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"

namespace parka
{
	class EqualityExpressionSyntax : public ExpressionSyntax
	{
		ExpressionSyntax& _lhs;
		ExpressionSyntax& _rhs;
		EqualityType _type;

	public:

		EqualityExpressionSyntax(ExpressionSyntax& lhs, ExpressionSyntax& rhs, EqualityType type) :
		_lhs(lhs),
		_rhs(rhs),
		_type(type)
		{}
		EqualityExpressionSyntax(EqualityExpressionSyntax&&) = default;
		EqualityExpressionSyntax(const EqualityExpressionSyntax&) = delete;

		static ExpressionSyntax *parse(Token& token);
		ExpressionContext *validate(SymbolTable& symbolTable);

		ExpressionType expressionType() const { return ExpressionType::Equality; }
		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
		const auto& type() const { return _type; }
	};
}

#endif
