#ifndef PARKA_SYNTAX_EXPRESSION_INDEX_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_INDEX_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"

#include <utility>

namespace parka
{
	class SubscriptExpressionSyntax : public ExpressionSyntax
	{
		ExpressionId _primary;
		ExpressionId _index;

		SubscriptExpressionSyntax(ExpressionId primary, ExpressionId index) :
		_primary(primary),
		_index(index)
		{}

	public:

		static Optional<ExpressionId> parse(Token& token, ExpressionId primary);

		bool validate(const EntityId& functionId);
		Optional<Type> getType() const;

		const auto& expression() const { return _primary; }
		const auto& index() const { return _index; }
	};
}

#endif
