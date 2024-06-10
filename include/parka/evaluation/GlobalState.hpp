#ifndef PARKA_EVALUATION_GLOBAL_STATE_HPP
#define PARKA_EVALUATION_GLOBAL_STATE_HPP

#include "parka/evaluation/Value.hpp"
#include "parka/ir/EntityIr.hpp"

namespace parka::evaluation
{
	class GlobalState
	{
	public:

		GlobalState();
		GlobalState(GlobalState&&) = default;
		GlobalState(const GlobalState&) = delete;

		Value& add(ir::EntityIr* key, const ir::TypeIr& type);
	};
}

#endif
