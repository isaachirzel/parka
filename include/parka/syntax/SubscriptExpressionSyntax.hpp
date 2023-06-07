#ifndef PARKA_SYNTAX_EXPRESSION_INDEX_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_INDEX_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"

#include <utility>

namespace parka
{
	class SubscriptExpressionSyntax : public ExpressionSyntax
	{
		ExpressionSyntaxId _primary;
		ExpressionSyntaxId _index;

		SubscriptExpressionSyntax(ExpressionSyntaxId primary, ExpressionSyntaxId index) :
		_primary(primary),
		_index(index)
		{}

	public:

		SubscriptExpressionSyntax(SubscriptExpressionSyntax&&) = default;
		SubscriptExpressionSyntax(const SubscriptExpressionSyntax&) = delete;

		static Optional<ExpressionSyntaxId> parse(Token& token, ExpressionSyntaxId primary);

		const auto& expression() const { return _primary; }
		const auto& index() const { return _index; }
	};
}

#endif
