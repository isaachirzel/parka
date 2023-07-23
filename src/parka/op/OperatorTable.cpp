#include "parka/op/OperatorTable.hpp"
#include "parka/log/Log.hpp"

namespace parka::op
{
	ir::OperatorIr *OperatorTable::find(OperatorType type, ir::ExpressionIr& a, ir::ExpressionIr *b)
	{
		for (auto& op : _operators)
		{
			if (op.operatorType() != type)
				continue;

			if (op.leftType() != a.type())
				continue;

			const auto *rightType = op.rightType();

			if (rightType != nullptr && b == nullptr)
				continue;

			if (*rightType != b->type())
				continue;

			return &op;
		}

		log::error("No operator exists for this expression.");

		return {};
	}
}
