#include "parka/evaluation/IntrinsicAssignmentOperator.hpp"

namespace parka::evaluation
{
	FlatMap<AssignmentOperatorKey, IntrinsicAssignmentOperator> getIntrinsicAssignmentOperators()
	{
		auto ops = FlatMap<AssignmentOperatorKey, IntrinsicAssignmentOperator>(128);

		return ops;
	}
}
