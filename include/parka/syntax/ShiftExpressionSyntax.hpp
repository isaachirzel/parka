#ifndef PARKA_SYNTAX_EXPRESSION_SHIFT_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_SHIFT_SYNTAX_HPP

#include "parka/enum/ShiftType.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"

namespace parka
{
	class ShiftExpressionSyntax : public ExpressionSyntax
	{
		const ExpressionSyntax& _lhs;
		const ExpressionSyntax& _rhs;
		ShiftType _type;

		ShiftExpressionSyntax(const ExpressionSyntax& lhs, const ExpressionSyntax& rhs, ShiftType type) :
		_lhs(lhs),
		_rhs(rhs),
		_type(type)
		{}

	public:

		ShiftExpressionSyntax(ShiftExpressionSyntax&&) = default;
		ShiftExpressionSyntax(const ShiftExpressionSyntax&) = delete;

		static const ExpressionSyntax *parse(Token& token);

		ExpressionType expressionType() const { return ExpressionType::Shift; }
		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
	};
}

#endif
