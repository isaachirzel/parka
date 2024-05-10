#ifndef PARKA_IR_BLOCK_STATEMENT_IR_HPP
#define PARKA_IR_BLOCK_STATEMENT_IR_HPP

#include "parka/ir/StatementIr.hpp"
#include "parka/util/Array.hpp"

namespace parka::ir
{
	class BlockStatementIr: public StatementIr
	{
		Array<StatementIr*> _statements;

	public:

		BlockStatementIr(Array<StatementIr*>&& statements):
			StatementIr(StatementType::Block),
			_statements(std::move(statements))
		{}
		BlockStatementIr(BlockStatementIr&&) = default;
		BlockStatementIr(const BlockStatementIr&) = delete;

		const auto& statements() const { return _statements; }
	};
}

#endif
