#include "parka/validation/AssignmentOperatorKey.hpp"
#include "parka/enum/AssignmentType.hpp"
#include "parka/util/Hash.hpp"

namespace parka::validation
{
	AssignmentOperatorKey::AssignmentOperatorKey():
		_left(ir::TypeIr::voidType),
		_right(ir::TypeIr::voidType),
		_assignmentType(AssignmentType::Assign)
	{}

	AssignmentOperatorKey::AssignmentOperatorKey(const ir::TypeIr& left, const ir::TypeIr& right, AssignmentType assignmentType):
		_left(left),
		_right(right),
		_assignmentType(assignmentType)
	{}

	bool AssignmentOperatorKey::operator==(const AssignmentOperatorKey& other) const
	{
		return _left == other._left && _right == other._right && _assignmentType == other._assignmentType;
	}
}

std::size_t std::hash<parka::validation::AssignmentOperatorKey>::operator()(const parka::validation::AssignmentOperatorKey& key) const
{
	// TODO: Idk lol figure out how to hash the enum
	auto typeHasher = std::hash<parka::ir::TypeIr>();

	return typeHasher(key._left) ^ typeHasher(key._right) ^ parka::hashNumber((size_t)key._assignmentType);
}
