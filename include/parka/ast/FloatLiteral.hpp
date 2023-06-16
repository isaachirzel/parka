#ifndef PARKA_SYNTAX_EXPRESSION_LITERAL_FLOAT_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_LITERAL_FLOAT_SYNTAX_HPP

#include "parka/ast/Literal.hpp"

namespace parka
{
	class FloatLiteralSyntax : public ExpressionSyntax
	{
		Snippet _snippet;

	public:

		FloatLiteralSyntax(const Snippet& snippet) :
		_snippet(snippet)
		{}
		FloatLiteralSyntax(FloatLiteralSyntax&&) = default;
		FloatLiteralSyntax(const FloatLiteralSyntax&) = delete;

		static ExpressionSyntax *parse(Token& token);
		ExpressionContext *validate(SymbolTable& symbolTable);

		// TODO: Actually determine size of float
		ExpressionType expressionType() const { return ExpressionType::FloatLiteral; }
		const Snippet& snippet() const { return _snippet; }
	};
}

#endif
