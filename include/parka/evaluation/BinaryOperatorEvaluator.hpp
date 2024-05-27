#include "parka/evaluation/LocalState.hpp"
#include "parka/evaluation/Value.hpp"
#include "parka/ir/BinaryOperatorIr.hpp"

namespace parka::evaluation
{
	Value& evaluateBinaryOperator(const ir::BinaryOperatorIr& op, Value& left, Value& right, LocalState& state);
}
