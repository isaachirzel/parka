#ifndef PARKA_CONTEXT_EXPRESSION_CONTEXT_HPP
#define PARKA_CONTEXT_EXPRESSION_CONTEXT_HPP

#include "parka/repository/ExpressionSyntaxId.hpp"
namespace parka
{
	struct ExpressionContext
	{
		virtual ~ExpressionContext() {}

		static Optional<ExpressionContextId> validate(const ExpressionSyntaxId& syntaxId);
	};
}

#endif
