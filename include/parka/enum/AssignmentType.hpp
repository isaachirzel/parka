#ifndef PARKA_ENUM_ASSIGNMENT_TYPE_HPP
#define PARKA_ENUM_ASSIGNMENT_TYPE_HPP

#include "parka/util/Common.hpp"
#include <ostream>

namespace parka
{
	enum class AssignmentType: u8
	{
		Assign,
		AddAssign,
		SubtractAssign,
		MultiplyAssign,
		DivideAssign,
		ModulusAssign,
		LeftShiftAssign,
		RightShiftAssign,
		BitwiseOrAssign,
		BitwiseXorAssign,
		BitwiseAndAssign
	};

	std::ostream& operator<<(std::ostream& out, const AssignmentType& type);
}

#endif
