#ifndef PARKA_IR_OPERATOR_HPP
#define PARKA_IR_OPERATOR_HPP

#include "parka/enum/OperatorType.hpp"
#include "parka/ir/Type.hpp"

namespace parka::ir
{
	struct OperatorIr
	{
		const bool isIntrinsic;

		OperatorIr(bool isIntrinsic):
			isIntrinsic(isIntrinsic)
		{}

		virtual ~OperatorIr() {}
		virtual const OperatorType& operatorType() const = 0;
		virtual const Type& returnType() const = 0;
		virtual const Type& leftType() const = 0;
		virtual const Type* rightType() const = 0;
	};
}

#endif
