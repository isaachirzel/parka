#ifndef PARKA_ENUM_STATEMENT_TYPE_HPP
#define PARKA_ENUM_STATEMENT_TYPE_HPP

#include <ostream>

namespace parka
{
	enum class StatementType
	{
		Declaration,
		Expression,
		Jump
	};

	std::ostream& operator<<(std::ostream& out, const StatementType& type);
}

#endif
