#ifndef PARKA_SYNTAX_EXPRESSION_BITWISE_XOR_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_BITWISE_XOR_SYNTAX_HPP

#include "parka/ast/Expression.hpp"

namespace parka
{
	class BitwiseXorExpressionSyntax : public ExpressionSyntax
	{
		Snippet _snippet;
		ExpressionSyntax& _lhs;
		ExpressionSyntax& _rhs;

	public:

		BitwiseXorExpressionSyntax(ExpressionSyntax& lhs, ExpressionSyntax& rhs) :
		_snippet(lhs.snippet() + rhs.snippet()),
		_lhs(lhs),
		_rhs(rhs)
		{}
		BitwiseXorExpressionSyntax(BitwiseXorExpressionSyntax&&) = default;
		BitwiseXorExpressionSyntax(const BitwiseXorExpressionSyntax&) = delete;

		static ExpressionSyntax *parse(Token& token);
		ExpressionContext *validate(SymbolTable& symbolTable);

		ExpressionType expressionType() const { return ExpressionType::BitwiseXor; }
		const Snippet& snippet() const { return _snippet; }
		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
	};
}

#endif
