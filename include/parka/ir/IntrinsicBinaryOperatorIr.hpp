#ifndef PARKA_IR_INTRINSIC_OPERATOR_HPP
#define PARKA_IR_INTRINSIC_OPERATOR_HPP

#include "parka/ir/BinaryOperatorIr.hpp"
#include "parka/ir/TypeIr.hpp"

namespace parka::ir
{
	class IntrinsicBinaryOperatorIr: public BinaryOperatorIr
	{
		const TypeIr& _leftType;
		const TypeIr& _rightType;
		const TypeIr& _returnType;
		BinaryExpressionType _binaryExpressionType;
		
	public:

		static IntrinsicBinaryOperatorIr entries[];
		static const usize entryCount;

	public:

		IntrinsicBinaryOperatorIr(BinaryExpressionType binaryExpressionType, const TypeIr& lhs, const TypeIr& rhs, const TypeIr& returnType);
		IntrinsicBinaryOperatorIr(IntrinsicBinaryOperatorIr&&) = default;
		IntrinsicBinaryOperatorIr(const IntrinsicBinaryOperatorIr&) = delete;

		const BinaryExpressionType& binaryExpressionType() const { return _binaryExpressionType; }
		const TypeIr& returnType() const { return _returnType; }
		const TypeIr& leftType() const { return _leftType; }
		const TypeIr& rightType() const { return _rightType; }
	};
}

#endif
