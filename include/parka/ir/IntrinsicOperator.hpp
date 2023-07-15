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
		Array<Type> _types;
		Type _returnType;
		OperatorType _operatorType;

	public:

		static const IntrinsicOperatorIr entries[];
		static const usize entryCount;

	private:

		IntrinsicOperatorIr(OperatorType operatorType, Array<Type>&& types, const Type& returnType);

	public:

		IntrinsicOperatorIr(IntrinsicOperatorIr&&) = default;
		IntrinsicOperatorIr(const IntrinsicOperatorIr&) = delete;
	};
}

#endif
