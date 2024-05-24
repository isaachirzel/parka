#ifndef PARKA_EVALUATION_INTRINSIC_ASSIGNMENT_OPERATOR_HPP
#define PARKA_EVALUATION_INTRINSIC_ASSIGNMENT_OPERATOR_HPP

#include "parka/validation/AssignmentOperatorKey.hpp"

namespace parka::evaluation
{

	class Value;
	class LocalState;

	typedef void (*IntrinsicAssignmentOperator) (Value& left, const Value& right);

	FlatMap<validation::AssignmentOperatorKey, IntrinsicAssignmentOperator> getIntrinsicAssignmentOperators();
}

#endif
