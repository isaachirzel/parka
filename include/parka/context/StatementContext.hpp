#ifndef PARKA_CONTEXT_STATEMENT_CONTEXT_HPP
#define PARKA_CONTEXT_STATEMENT_CONTEXT_HPP

#include "parka/enum/StatementType.hpp"

namespace parka
{
	struct StatementContext
	{
		virtual ~StatementContext() {}
		virtual StatementType statementType() const = 0;
	};
}

#endif
