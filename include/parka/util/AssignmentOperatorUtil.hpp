#ifndef PARKA_UTIL_ASSIGNMENT_OPERATOR_UTIL_HPP
#define PARKA_UTIL_ASSIGNMENT_OPERATOR_UTIL_HPP

#include "parka/ir/AssignmentOperatorIr.hpp"
#include "parka/util/TypeUtil.hpp"

namespace parka
{
	template <AssignmentType assignmentType, typename Left, typename Right = Left>
	ir::AssignmentOperatorIr& assgn()
	{
		static ir::AssignmentOperatorIr op(type<Left>(), type<Right>(), assignmentType);

		return op;
	}
}

#endif
