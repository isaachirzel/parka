#ifndef PARKA_IR_EXPRESSION_HPP
#define PARKA_IR_EXPRESSION_HPP

#include "parka/enum/ExpressionType.hpp"
#include "parka/ir/Value.hpp"
#include "parka/ir/Type.hpp"

namespace parka::ir
{
	struct ExpressionIr: public Value
	{
		const ExpressionType expressionType;

	public:

		ExpressionIr(ExpressionType expressionType):
		expressionType(expressionType)
		{}
		virtual ~ExpressionIr() {}

		virtual const Type& type() const = 0;
	};
}

#endif
