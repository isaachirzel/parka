#include "parka/ir/AssignmentOperatorIr.hpp"

namespace parka::ir
{
	FlatMap<AssignmentOperatorKey, ir::AssignmentOperatorIr*> AssignmentOperatorIr::getIntrinsicAssignmentOperators()
	{
		auto ops = FlatMap<AssignmentOperatorKey, ir::AssignmentOperatorIr*>(256);

		return ops;
	}

	AssignmentOperatorIr::AssignmentOperatorIr(const ir::TypeIr& left, const ir::TypeIr& right, AssignmentType assignmentType):
		_left(left),
		_right(right),
		_assignmentType(assignmentType)
	{}
}