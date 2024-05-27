#include "parka/evaluation/LocalState.hpp"
#include "parka/evaluation/Value.hpp"
#include "parka/ir/AssignmentOperatorIr.hpp"

namespace parka::evaluation
{
	void evaluateAssignmentOperator(const ir::AssignmentOperatorIr& op, Value& left, Value& right, LocalState& state);
}
