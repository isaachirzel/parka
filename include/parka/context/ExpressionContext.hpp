#ifndef PARKA_CONTEXT_EXPRESSION_CONTEXT_HPP
#define PARKA_CONTEXT_EXPRESSION_CONTEXT_HPP

#include "parka/enum/ExpressionType.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/repository/ExpressionContextId.hpp"

namespace parka
{
	struct ExpressionContext
	{
		virtual ~ExpressionContext() {}
		virtual ExpressionType expressionType() const = 0;

		static const ExpressionContext& create(ExpressionContext&& context);
		static ExpressionContextId idFor(const ExpressionContext& Context);
	};
}

#endif
