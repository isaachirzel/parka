#ifndef PARKA_SYNTAX_EXPRESSION_SHIFT_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_SHIFT_SYNTAX_HPP

#include "parka/enum/ShiftType.hpp"
#include "parka/ast/Expression.hpp"

namespace parka
{
	class ShiftExpressionSyntax : public ExpressionSyntax
	{
		Snippet _snippet;
		ExpressionSyntax& _lhs;
		ExpressionSyntax& _rhs;
		ShiftType _type;

	public:

		ShiftExpressionSyntax(ExpressionSyntax& lhs, ExpressionSyntax& rhs, ShiftType type) :
		_snippet(lhs.snippet() + rhs.snippet()),
		_lhs(lhs),
		_rhs(rhs),
		_type(type)
		{}
		ShiftExpressionSyntax(ShiftExpressionSyntax&&) = default;
		ShiftExpressionSyntax(const ShiftExpressionSyntax&) = delete;

		static ExpressionSyntax *parse(Token& token);
		ExpressionContext *validate(SymbolTable& symbolTable);

		ExpressionType expressionType() const { return ExpressionType::Shift; }
		const Snippet& snippet() const { return _snippet; }

		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
	};
}

#endif
