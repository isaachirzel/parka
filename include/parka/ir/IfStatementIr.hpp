#ifndef PARKA_IR_IF_STATEMENT_IR_HPP
#define PARKA_IR_IF_STATEMENT_IR_HPP

#include "parka/ir/StatementIr.hpp"

namespace parka::ir
{
	class IfStatementIr: public StatementIr
	{
	public:

		IfStatementIr():
			StatementIr(StatementType::If)
		{}
		IfStatementIr(IfStatementIr&&) = default;
		IfStatementIr(const IfStatementIr&) = delete;
	};
}

#endif
