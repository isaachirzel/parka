#ifndef PARKA_EVALUATION_GLOBAL_STATE_HPP
#define PARKA_EVALUATION_GLOBAL_STATE_HPP

#include "parka/evaluation/Value.hpp"
#include "parka/ir/LValueIr.hpp"
#include "parka/util/Table.hpp"

namespace parka::evaluation
{
	class GlobalState
	{
		Table<ir::LValueIr*, Value> _values;

	public:

		GlobalState() = default;
		GlobalState(GlobalState&&) = default;
		GlobalState(const GlobalState&) = delete;

		Value& add(ir::LValueIr *key, const ir::TypeIr& type);
	};
}

#endif
