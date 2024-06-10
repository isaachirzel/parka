#include "parka/evaluation/GlobalState.hpp"
#include "parka/log/Log.hpp"

namespace parka::evaluation
{
	GlobalState::GlobalState() {}

	Value& GlobalState::add(ir::EntityIr*, const ir::TypeIr&)
	{
		log::notImplemented(here());
	}
}
