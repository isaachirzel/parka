#ifndef PARKA_SYNTAX_IF_EXPRESSION_SYNTAX_HPP
#define PARKA_SYNTAX_IF_EXPRESSION_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/repository/StatementSyntaxId.hpp"

// TODO: Consider merging this with conditional expression

namespace parka
{
	class IfExpressionSyntax : public ExpressionSyntax
	{
		// ExpressionSyntaxId _condition;
		// StatementSyntaxId _thenCase;

		// union
		// {
		// 	StatementSyntaxId _elseCase;
		// 	ExpressionSyntaxId _elseIf;
		// };

		// IfType _type;
	};
}

#endif
