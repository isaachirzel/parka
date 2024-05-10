#ifndef PARKA_IR_CONTINUE_STATEMENT_IR
#define PARKA_IR_CONTINUE_STATEMENT_IR

#include "parka/ir/StatementIr.hpp"

namespace parka::ir
{
	class ContinueStatementIr: public StatementIr
	{
	public:

		ContinueStatementIr():
			StatementIr(StatementType::Continue)
		{}
		ContinueStatementIr(ContinueStatementIr&&) = default;
		ContinueStatementIr(const ContinueStatementIr&) = delete;
	};
}

#endif
