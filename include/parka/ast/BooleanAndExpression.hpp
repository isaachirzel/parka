#ifndef PARKA_SYNTAX_EXPRESSION_BOOLEAN_AND_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_BOOLEAN_AND_SYNTAX_HPP

#include "parka/ast/Expression.hpp"

namespace parka
{
	class BooleanAndExpressionSyntax : public ExpressionSyntax
	{
		ExpressionSyntax& _lhs;
		ExpressionSyntax& _rhs;

	public:

		BooleanAndExpressionSyntax(ExpressionSyntax& lhs, ExpressionSyntax& rhs) :
		_lhs(lhs),
		_rhs(rhs)
		{}
		BooleanAndExpressionSyntax(BooleanAndExpressionSyntax&&) = default;
		BooleanAndExpressionSyntax(const BooleanAndExpressionSyntax&) = delete;
		
		static ExpressionSyntax *parse(Token& token);
		ExpressionContext *validate(SymbolTable& symbolTable);

		ExpressionType expressionType() const { return ExpressionType::BooleanAnd; }
		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
	};
}

#endif
