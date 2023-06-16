#ifndef PARKA_SYNTAX_IF_EXPRESSION_SYNTAX_HPP
#define PARKA_SYNTAX_IF_EXPRESSION_SYNTAX_HPP

#include "parka/ast/Expression.hpp"

// TODO: Consider merging this with conditional expression

namespace parka
{
	class IfExpressionSyntax : public ExpressionSyntax
	{
		Snippet _snippet;

	public:

		static ExpressionSyntax	*parse(Token& token);
		ExpressionContext *validate(SymbolTable& symbolTable);

		ExpressionType expressionType() const { return ExpressionType::If; }
		const Snippet& snippet() const { return _snippet; }
	};
}

#endif
