#ifndef PARKA_EVALUATION_INTRINSIC_FUNCTION_EVALUATOR_HPP
#define PARKA_EVALUATION_INTRINSIC_FUNCTION_EVALUATOR_HPP

#include "parka/enum/IntrinsicFunctionType.hpp"
#include "parka/evaluation/LocalState.hpp"

namespace parka::evaluation
{
	void evaluateIntrinsicFunction(IntrinsicFunctionType intrinsicFunctionType, LocalState& state);
}

#endif
