#ifndef PARKA_SYNTAX_EXPRESSION_INDEX_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_INDEX_SYNTAX_HPP

#include "parka/ast/Expression.hpp"

#include <utility>

namespace parka
{
	class SubscriptExpressionSyntax : public ExpressionSyntax
	{
		Snippet _snippet;
		ExpressionSyntax& _primary;
		ExpressionSyntax& _index;

	public:

		SubscriptExpressionSyntax(const Snippet& snippet, ExpressionSyntax& primary, ExpressionSyntax& index) :
		_snippet(snippet),
		_primary(primary),
		_index(index)
		{}
		SubscriptExpressionSyntax(SubscriptExpressionSyntax&&) = default;
		SubscriptExpressionSyntax(const SubscriptExpressionSyntax&) = delete;

		static ExpressionSyntax *parse(Token& token, ExpressionSyntax& primary);
		ExpressionContext *validate(SymbolTable& symbolTable);

		ExpressionType expressionType() const { return ExpressionType::Subscript; }
		const Snippet& snippet() const { return _snippet; }
		const auto& expression() const { return _primary; }
		const auto& index() const { return _index; }
	};
}

#endif
