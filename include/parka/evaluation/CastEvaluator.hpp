#include "parka/evaluation/LocalState.hpp"
#include "parka/evaluation/Value.hpp"
#include "parka/ir/CastIr.hpp"

namespace parka::evaluation
{
	Value& evaluateCast(const ir::CastIr& ir, Value& from, Value& to, LocalState& state);
}
