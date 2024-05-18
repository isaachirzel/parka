#ifndef PARKA_EVALUATION_INTRINSIC_BINARY_OPERATOR_HPP
#define PARKA_EVALUATION_INTRINSIC_BINARY_OPERATOR_HPP

#include "parka/evaluation/LocalState.hpp"
#include "parka/evaluation/Value.hpp"

namespace parka::evaluation
{
	using IntrinsicBinaryOperator = std::function<Value& (Value& left, Value& right, LocalState& state)>;

	extern IntrinsicBinaryOperator intrinsicBinaryOperators[];
	extern const usize intrinsicBinaryOperatorCount;
}

#endif
