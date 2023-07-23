#ifndef PARKA_IR_INTRINSIC_OPERATOR_HPP
#define PARKA_IR_INTRINSIC_OPERATOR_HPP

#include "parka/enum/OperatorType.hpp"
#include "parka/ir/Operator.hpp"
#include "parka/ir/Type.hpp"
#include "parka/util/Array.hpp"

namespace parka::ir
{
	class IntrinsicOperatorIr: public OperatorIr
	{
		const Type& _lhs;
		const Type *_rhs;
		const Type& _returnType;
		OperatorType _operatorType;

	public:

		static const IntrinsicOperatorIr entries[];
		static const usize entryCount;

	private:

		IntrinsicOperatorIr(OperatorType operatorType, const Type& type, const Type& returnType);
		IntrinsicOperatorIr(OperatorType operatorType, const Type& lhs, const Type& rhs, const Type& returnType);

	public:

		IntrinsicOperatorIr(IntrinsicOperatorIr&&) = default;
		IntrinsicOperatorIr(const IntrinsicOperatorIr&) = delete;

		const OperatorType& operatorType() const { return _operatorType; }
		const Type& leftType() const { return _lhs; }
		const Type *rightType() const { return _rhs; }
	};
}

#endif
