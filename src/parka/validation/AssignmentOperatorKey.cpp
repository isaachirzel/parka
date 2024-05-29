#include "parka/validation/AssignmentOperatorKey.hpp"
#include "parka/enum/AssignmentType.hpp"
#include "parka/ir/VoidPrimitiveIr.hpp"
#include "parka/util/Hash.hpp"

namespace parka::validation
{
	AssignmentOperatorKey::AssignmentOperatorKey():
		_left(&ir::VoidPrimitiveIr::instance),
		_right(&ir::VoidPrimitiveIr::instance),
		_assignmentType(AssignmentType::Assign)
	{}

	AssignmentOperatorKey::AssignmentOperatorKey(const ir::TypeIr& left, const ir::TypeIr& right, AssignmentType assignmentType):
		_left(&left),
		_right(&right),
		_assignmentType(assignmentType)
	{}

	bool AssignmentOperatorKey::operator==(const AssignmentOperatorKey& other) const
	{
		return _left == other._left && _right == other._right && _assignmentType == other._assignmentType;
	}
}

std::size_t std::hash<parka::validation::AssignmentOperatorKey>::operator()(const parka::validation::AssignmentOperatorKey& key) const
{
	return parka::hashNumber((size_t)key._left ^ (size_t)key._right) ^ parka::hashNumber((size_t)key._assignmentType);
}
