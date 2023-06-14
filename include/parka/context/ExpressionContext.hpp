#ifndef PARKA_CONTEXT_EXPRESSION_CONTEXT_HPP
#define PARKA_CONTEXT_EXPRESSION_CONTEXT_HPP

#include "parka/enum/ExpressionType.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/repository/ExpressionContextId.hpp"
#include "parka/type/ValueType.hpp"

namespace parka
{
	struct ExpressionContext
	{
		virtual ~ExpressionContext() {}
		virtual const ValueType& valueType() const = 0;
		virtual ExpressionType expressionType() const = 0;

		static const ExpressionContext& create(ExpressionContext&& context);
		static ExpressionContextId idFor(const ExpressionContext& Context);
	};
}

#endif
