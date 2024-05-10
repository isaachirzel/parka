#ifndef PARKA_ENUM_STATEMENT_TYPE_HPP
#define PARKA_ENUM_STATEMENT_TYPE_HPP

#include "parka/util/Common.hpp"

namespace parka
{
	enum class StatementType: u8
	{
		Declaration,
		Expression,
		Return,
		Break,
		Continue,
		Yield,
		For,
		Block
	};

	std::ostream& operator<<(std::ostream& out, const StatementType& type);
}

#endif
