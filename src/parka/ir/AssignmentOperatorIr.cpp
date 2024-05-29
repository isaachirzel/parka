#include "parka/ir/AssignmentOperatorIr.hpp"
#include "parka/enum/AssignmentType.hpp"

namespace parka::ir
{
	AssignmentOperatorIr::AssignmentOperatorIr(const ir::TypeIr& left, const ir::TypeIr& right, AssignmentType assignmentType):
		_left(left),
		_right(right),
		_assignmentType(assignmentType)
	{}
}
