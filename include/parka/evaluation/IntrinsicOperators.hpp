#ifndef PARKA_EVALUATION_INTRINSIC_OPERATOR_HPP
#define PARKA_EVALUATION_INTRINSIC_OPERATOR_HPP

#include "parka/evaluation/State.hpp"
#include "parka/evaluation/Value.hpp"

namespace parka::evaluation
{
	using IntrinsicOperator = std::function<Value&(Value&, Value&, State& state)>;

	extern IntrinsicOperator intrinsicOperators[];
	extern const usize IntrinsicOperatorCount;
}

#endif