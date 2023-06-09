#ifndef PARKA_CONTEXT_EXPRESSION_CONTEXT_HPP
#define PARKA_CONTEXT_EXPRESSION_CONTEXT_HPP

#include "parka/symbol/SymbolTable.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/repository/ExpressionContextId.hpp"

namespace parka
{
	struct ExpressionContext
	{
		virtual ~ExpressionContext() {}
		virtual ExpressionType expressionType() const = 0;

		static const ExpressionContext *validate(const ExpressionSyntax& syntax, SymbolTable& symbolTable);
		static const ExpressionContext& create(ExpressionContext&& context);
		static ExpressionContextId idFor(const ExpressionContext& Context);
	};
}

#endif
