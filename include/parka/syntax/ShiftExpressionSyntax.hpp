#ifndef PARKA_SYNTAX_EXPRESSION_SHIFT_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_SHIFT_SYNTAX_HPP

#include "parka/enum/ShiftType.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"

namespace parka
{
	class ShiftExpressionSyntax : public ExpressionSyntax
	{
		ExpressionSyntax& _lhs;
		ExpressionSyntax& _rhs;
		ShiftType _type;

	public:

		ShiftExpressionSyntax(ExpressionSyntax& lhs, ExpressionSyntax& rhs, ShiftType type) :
		_lhs(lhs),
		_rhs(rhs),
		_type(type)
		{}
		ShiftExpressionSyntax(ShiftExpressionSyntax&&) = default;
		ShiftExpressionSyntax(const ShiftExpressionSyntax&) = delete;

		static ExpressionSyntax *parse(Token& token);
		ExpressionContext *validate(SymbolTable& symbolTable);

		ExpressionType expressionType() const { return ExpressionType::Shift; }
		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
	};
}

#endif
