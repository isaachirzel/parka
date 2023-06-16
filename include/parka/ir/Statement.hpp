#ifndef PARKA_IR_STATEMENT_HPP
#define PARKA_IR_STATEMENT_HPP

#include "parka/enum/StatementType.hpp"

namespace parka::ir
{
	struct StatementIr
	{
		virtual ~StatementIr() {}
		virtual StatementType statementType() const = 0;
	};
}

#endif
