#ifndef PARKA_SYNTAX_EXPRESSION_INDEX_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_INDEX_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"

#include <utility>

namespace parka
{
	class SubscriptExpressionSyntax : public ExpressionSyntax
	{
		const ExpressionSyntax& _primary;
		const ExpressionSyntax& _index;

	private:

		SubscriptExpressionSyntax(const ExpressionSyntax& primary, const ExpressionSyntax& index) :
		_primary(primary),
		_index(index)
		{}

	public:

		SubscriptExpressionSyntax(SubscriptExpressionSyntax&&) = default;
		SubscriptExpressionSyntax(const SubscriptExpressionSyntax&) = delete;

		static const ExpressionSyntax *parse(Token& token, const ExpressionSyntax& primary);

		ExpressionType expressionType() const { return ExpressionType::Subscript; }
		const auto& expression() const { return _primary; }
		const auto& index() const { return _index; }
	};
}

#endif
