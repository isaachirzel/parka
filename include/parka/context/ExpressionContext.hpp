#ifndef PARKA_CONTEXT_EXPRESSION_CONTEXT_HPP
#define PARKA_CONTEXT_EXPRESSION_CONTEXT_HPP

#include "parka/repository/ExpressionSyntax.hpp"

namespace parka
{
	struct ExpressionContext
	{
		virtual ~ExpressionContext() {}

		static Optional<ExpressionContextId> validate(const ExpressionSyntax& syntax);
	};
}

#endif
