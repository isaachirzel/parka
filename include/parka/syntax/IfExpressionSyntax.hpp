#ifndef PARKA_SYNTAX_IF_EXPRESSION_SYNTAX_HPP
#define PARKA_SYNTAX_IF_EXPRESSION_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/data/StatementId.hpp"

// TODO: Consider merging this with conditional expression

namespace parka
{
	enum class IfType
	{
		Then,
		ThenElse,
		ThenElseIf
	};

	class IfExpressionSyntax : public ExpressionSyntax
	{
		// ExpressionId _condition;
		// StatementId _thenCase;

		// union
		// {
		// 	StatementId _elseCase;
		// 	ExpressionId _elseIf;
		// };

		// IfType _type;
	};
}

#endif
