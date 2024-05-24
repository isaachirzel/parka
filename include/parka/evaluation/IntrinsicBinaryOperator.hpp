#ifndef PARKA_EVALUATION_INTRINSIC_BINARY_OPERATOR_HPP
#define PARKA_EVALUATION_INTRINSIC_BINARY_OPERATOR_HPP

#include "parka/symbol/BinaryOperatorKey.hpp"
#include "parka/util/FlatMap.hpp"

namespace parka::evaluation
{
	class Value;
	class LocalState;

	typedef Value& (*IntrinsicBinaryOperator) (Value& left, Value& right, LocalState& state);

	FlatMap<BinaryOperatorKey, IntrinsicBinaryOperator> getIntrinsicBinaryOperators();
}

#endif
