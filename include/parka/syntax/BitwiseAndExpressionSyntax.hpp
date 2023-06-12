#ifndef PARKA_SYNTAX_EXPRESSION_BITWISE_AND_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_BITWISE_AND_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"

namespace parka
{
	class BitwiseAndExpressionSyntax : public ExpressionSyntax
	{
		ExpressionSyntax& _lhs;
		ExpressionSyntax& _rhs;

	public:

		BitwiseAndExpressionSyntax(ExpressionSyntax& lhs, ExpressionSyntax& rhs) :
		_lhs(lhs),
		_rhs(rhs)
		{}
		BitwiseAndExpressionSyntax(BitwiseAndExpressionSyntax&&) = default;
		BitwiseAndExpressionSyntax(const BitwiseAndExpressionSyntax&) = delete;

		static ExpressionSyntax *parse(Token& token);
		ExpressionContext *validate(SymbolTable& symbolTable);

		ExpressionType expressionType() const { return ExpressionType::BitwiseAnd; }
		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
	};
}

#endif
