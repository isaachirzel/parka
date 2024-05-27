#include "parka/evaluation/LocalState.hpp"
#include "parka/evaluation/Value.hpp"
#include "parka/ir/ConversionIr.hpp"

namespace parka::evaluation
{
	Value& evaluateConversion(const ir::ConversionIr& conversion, Value& to, Value& from, LocalState& state);
}
