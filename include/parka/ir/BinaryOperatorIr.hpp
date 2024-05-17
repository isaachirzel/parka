#ifndef PARKA_IR_OPERATOR_HPP
#define PARKA_IR_OPERATOR_HPP

#include "parka/enum/BinaryExpressionType.hpp"
#include "parka/ir/TypeIr.hpp"

namespace parka::ir
{
	struct BinaryOperatorIr
	{
		const bool isIntrinsic;

		BinaryOperatorIr(bool isIntrinsic):
			isIntrinsic(isIntrinsic)
		{}

		virtual ~BinaryOperatorIr() {}
		virtual const TypeIr& leftType() const = 0;
		virtual const TypeIr& rightType() const = 0;
		virtual const TypeIr& returnType() const = 0;
		virtual const BinaryExpressionType& binaryExpressionType() const = 0;
	};
}

#endif
