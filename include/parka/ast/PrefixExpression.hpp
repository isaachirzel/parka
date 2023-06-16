#ifndef PARKA_SYNTAX_EXPRESSION_PREFIX_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_PREFIX_SYNTAX_HPP

#include "parka/enum/PrefixType.hpp"
#include "parka/ast/Expression.hpp"

#include "parka/parser/Token.hpp"

namespace parka
{
	class PrefixExpressionSyntax : public ExpressionSyntax
	{
		Snippet _snippet;
		ExpressionSyntax& _expression;
		PrefixType _type;

	public:

		PrefixExpressionSyntax(const Snippet& snippet, PrefixType type, ExpressionSyntax& expression) :
		_snippet(snippet),
		_expression(expression),
		_type(type)
		{}
		PrefixExpressionSyntax(PrefixExpressionSyntax&&) = default;
		PrefixExpressionSyntax(const PrefixExpressionSyntax&) = delete;

		static ExpressionSyntax *parse(Token& token);
		ExpressionContext *validate(SymbolTable& symbolTable);

		ExpressionType expressionType() const { return ExpressionType::Prefix; }
		const Snippet& snippet() const { return _snippet; }
		const auto& expression() const { return _expression; }
		const auto& type() const { return _type; }
	};
}

#endif
