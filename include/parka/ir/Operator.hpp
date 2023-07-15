#ifndef PARKA_IR_OPERATOR_HPP
#define PARKA_IR_OPERATOR_HPP

namespace parka::ir
{
	struct OperatorIr
	{
		const bool isIntrinsic;

		OperatorIr(bool isIntrinsic):
		isIntrinsic(isIntrinsic)
		{}
		virtual ~OperatorIr() {}
	};
}

#endif
