#ifndef PARKA_IR_YIELD_STATEMENT_IR
#define PARKA_IR_YIELD_STATEMENT_IR

#include "parka/ir/StatementIr.hpp"

namespace parka::ir
{
	class YieldStatementIr: public StatementIr
	{
	public:

		YieldStatementIr():
			StatementIr(StatementType::Yield)
		{}
		YieldStatementIr(YieldStatementIr&&) = default;
		YieldStatementIr(const YieldStatementIr&) = delete;
	};
}

#endif
