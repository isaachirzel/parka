#ifndef PARKA_EVALUATION_INTRINSIC_ASSIGNMENT_OPERATOR_HPP
#define PARKA_EVALUATION_INTRINSIC_ASSIGNMENT_OPERATOR_HPP

#include "parka/symbol/AssignmentOperatorKey.hpp"

namespace parka::evaluation
{

	class Value;
	class LocalState;

	typedef Value& (*IntrinsicAssignmentOperator) (Value& left, const Value& right, LocalState& state);

	FlatMap<AssignmentOperatorKey, IntrinsicAssignmentOperator> getIntrinsicAssignmentOperators();
}

#endif
