#ifndef PARKA_IR_BREAK_STATEMENT_IR
#define PARKA_IR_BREAK_STATEMENT_IR

#include "parka/ir/StatementIr.hpp"

namespace parka::ir
{
	class BreakStatementIr: public StatementIr
	{
	public:

		BreakStatementIr():
			StatementIr(StatementType::Break)
		{}
		BreakStatementIr(BreakStatementIr&&) = default;
		BreakStatementIr(const BreakStatementIr&) = delete;
	};
}

#endif
