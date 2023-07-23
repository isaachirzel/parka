#ifndef PARKA_OP_OPERATOR_TABLE_HPP
#define PARKA_OP_OPERATOR_TABLE_HPP

#include "parka/enum/OperatorType.hpp"
#include "parka/ir/Expression.hpp"
#include "parka/ir/Operator.hpp"
#include "parka/util/Array.hpp"

namespace parka::op
{
	class OperatorTable
	{
		// TODO: Optimize

		Array<ir::OperatorIr> _operators;

	public:

		OperatorTable() = default;
		OperatorTable(OperatorTable&&) = default;
		OperatorTable(const OperatorTable&) = delete;

		ir::OperatorIr *find(OperatorType type, ir::ExpressionIr& a, ir::ExpressionIr *b);
	};
}

#endif
