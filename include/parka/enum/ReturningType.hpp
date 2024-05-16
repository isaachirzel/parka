#ifndef PARKA_ENUM_RETURNING_TYPE_HPP
#define PARKA_ENUM_RETURNING_TYPE_HPP

#include "parka/util/Common.hpp"
#include <ostream>

namespace parka
{
	enum class ReturningType: u8
	{
		None,
		Return,
		Exception
	};

	std::ostream& operator<<(std::ostream& out, const ReturningType& type);
}

#endif
