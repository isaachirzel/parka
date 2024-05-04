#ifndef PARKA_IR_STATEMENT_HPP
#define PARKA_IR_STATEMENT_HPP

#include "parka/enum/StatementType.hpp"

namespace parka::ir
{
	struct StatementIr
	{
		const StatementType statementType;

	public:

		StatementIr(StatementType statementType):
			statementType(statementType)
		{}
		virtual ~StatementIr() {}
	};
}

#endif
