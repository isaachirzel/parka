#ifndef PARKA_IR_INTRINSIC_OPERATOR_HPP
#define PARKA_IR_INTRINSIC_OPERATOR_HPP

#include "parka/ir/BinaryOperatorIr.hpp"
#include "parka/ir/TypeIr.hpp"

namespace parka::ir
{
	class IntrinsicBinaryOperatorIr: public BinaryOperatorIr
	{
		const Type& _leftType;
		const Type& _rightType;
		const Type& _returnType;
		BinaryExpressionType _binaryExpressionType;
		
	public:

		static IntrinsicBinaryOperatorIr entries[];
		static const usize entryCount;

	public:

		IntrinsicBinaryOperatorIr(BinaryExpressionType binaryExpressionType, const Type& lhs, const Type& rhs, const Type& returnType);
		IntrinsicBinaryOperatorIr(IntrinsicBinaryOperatorIr&&) = default;
		IntrinsicBinaryOperatorIr(const IntrinsicBinaryOperatorIr&) = delete;

		const BinaryExpressionType& binaryExpressionType() const { return _binaryExpressionType; }
		const Type& returnType() const { return _returnType; }
		const Type& leftType() const { return _leftType; }
		const Type& rightType() const { return _rightType; }
	};
}

#endif
