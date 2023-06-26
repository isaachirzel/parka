#ifndef PARKA_IR_EXPRESSION_HPP
#define PARKA_IR_EXPRESSION_HPP

#include "parka/enum/ExpressionType.hpp"
#include "parka/ir/ValueType.hpp"

namespace parka::ir
{
	struct ExpressionIr
	{
		const ExpressionType expressionType;

	public:

		ExpressionIr(ExpressionType expressionType):
		expressionType(expressionType)
		{}
		virtual ~ExpressionIr() {}

		virtual const ValueType& valueType() const = 0;
	};
}

#endif
