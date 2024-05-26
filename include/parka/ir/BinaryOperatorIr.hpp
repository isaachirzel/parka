#ifndef PARKA_IR_BINARY_OPERATOR_IR_HPP
#define PARKA_IR_BINARY_OPERATOR_IR_HPP

#include "parka/enum/BinaryExpressionType.hpp"
#include "parka/ir/TypeIr.hpp"
#include "parka/validation/BinaryOperatorKey.hpp"
#include "parka/util/FlatMap.hpp"

namespace parka::ir
{
	class BinaryOperatorIr
	{
		const TypeIr& _leftType;
		const TypeIr& _rightType;
		const TypeIr& _returnType;
		BinaryExpressionType _binaryExpressionType;
		
	public:

		static FlatMap<validation::BinaryOperatorKey, BinaryOperatorIr*> getIntrinsicBinaryOperators();

	public:

		BinaryOperatorIr(BinaryExpressionType binaryExpressionType, const TypeIr& leftType, const TypeIr& rightType, const TypeIr& returnType);
		BinaryOperatorIr(BinaryOperatorIr&&) = default;
		BinaryOperatorIr(const BinaryOperatorIr&) = default;

		const BinaryExpressionType& binaryExpressionType() const { return _binaryExpressionType; }
		const TypeIr& returnType() const { return _returnType; }
		const TypeIr& leftType() const { return _leftType; }
		const TypeIr& rightType() const { return _rightType; }
	};
}

#endif
