#include "parka/evaluation/GlobalState.hpp"
#include "parka/log/Log.hpp"

namespace parka::evaluation
{
	GlobalState::GlobalState():
		_intrinsicBinaryOperators(),
		_intrinsicAssignmentOperators(),
		_intrinsicConversions()
	{}

	Value& GlobalState::add(ir::EntityIr*, const ir::TypeIr&)
	{
		log::notImplemented(here());
	}
}
