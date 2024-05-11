#ifndef PARKA_ENUM_ASSIGNMENT_TYPE_HPP
#define PARKA_ENUM_ASSIGNMENT_TYPE_HPP

#include "parka/util/Common.hpp"
#include <ostream>

namespace parka
{
	enum class AssignmentType: u8
	{
		Assign,
		MultiplyAssign,
		DivideAssign,
		ModulusAssign,
		AddAssign,
		SubtractAssign,
		LeftShiftAssign,
		RightShiftAssign,
		BitwiseAndAssign,
		BitwiseOrAssign,
		BitwiseXorAssign
	};

	std::ostream& operator<<(std::ostream& out, const AssignmentType& type);
}

#endif
