#ifndef PARKA_ENUM_RETURNING_TYPE_HPP
#define PARKA_ENUM_RETURNING_TYPE_HPP

#include "parka/util/Common.hpp"
#include <ostream>

namespace parka
{
	enum class JumpType: u8
	{
		None,
		Return,
		Break,
		Continue,
		Exception
	};

	std::ostream& operator<<(std::ostream& out, const JumpType& type);
}

#endif
