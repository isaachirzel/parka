#ifndef PARKA_IR_ASSIGNMENT_OPERATOR_IR_HPP
#define PARKA_IR_ASSIGNMENT_OPERATOR_IR_HPP

#include "parka/enum/AssignmentType.hpp"
#include "parka/symbol/AssignmentOperatorKey.hpp"
#include "parka/util/FlatMap.hpp"

namespace parka::ir
{
	class AssignmentOperatorIr
	{
		ir::TypeIr _left;
		ir::TypeIr _right;
		AssignmentType _assignmentType;

	public:

		static FlatMap<AssignmentOperatorKey, AssignmentOperatorIr*> getIntrinsicAssignmentOperators();

	public:

		AssignmentOperatorIr(const ir::TypeIr& left, const ir::TypeIr& right, AssignmentType assignmentType);
		AssignmentOperatorIr(AssignmentOperatorIr&&) = default;
		AssignmentOperatorIr(const AssignmentOperatorIr&) = delete;

		const auto& left() const { return _left; }
		const auto& right() const { return _right; }
		const auto& assignmentType() const { return _assignmentType; }
	};
}

#endif
