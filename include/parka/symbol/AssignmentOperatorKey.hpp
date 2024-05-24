#ifndef PARKA_SYMBOL_ASSIGNMENT_OPERATOR_KEY_HPP
#define PARKA_SYMBOL_ASSIGNMENT_OPERATOR_KEY_HPP

#include "parka/enum/AssignmentType.hpp"
#include "parka/ir/TypeIr.hpp"

namespace parka
{
	class AssignmentOperatorKey
	{
		ir::TypeIr _left;
		ir::TypeIr _right;
		AssignmentType _assignmentType;

	public:

		AssignmentOperatorKey();
		AssignmentOperatorKey(const ir::TypeIr& left, const ir::TypeIr& right, AssignmentType assignmentType);
		AssignmentOperatorKey(AssignmentOperatorKey&&) = default;
		AssignmentOperatorKey(const AssignmentOperatorKey&) = default;
		AssignmentOperatorKey& operator=(AssignmentOperatorKey&&) = default;
		AssignmentOperatorKey& operator=(const AssignmentOperatorKey&) = default;

		bool operator==(const AssignmentOperatorKey& other) const;

		friend struct std::hash<AssignmentOperatorKey>;
	};
}

template<>
struct std::hash<parka::AssignmentOperatorKey>
{
	std::size_t operator()(const parka::AssignmentOperatorKey& key) const;
};

#endif
