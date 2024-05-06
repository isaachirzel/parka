#include "parka/evaluation/IntrinsicOperators.hpp"
#include "parka/log/Log.hpp"

namespace parka::evaluation
{
	Value& addIntToInt(Value& left, Value& right, State& state)
	{
		auto value = left.value() + right.value();
		auto& result = state.push(left.type(), value);

		return result;
	}

	Value& addFloatToFloat(Value& left, Value& right, State& state)
	{
		log::notImplemented(here());
	}

	IntrinsicOperator intrinsicOperators[] = {
		addIntToInt,
		addIntToInt,
		addIntToInt,
		addIntToInt,
		addIntToInt,
		addIntToInt,
		addIntToInt,
		addIntToInt,
		addIntToInt,
		addIntToInt,
		addIntToInt,
		addIntToInt,
		addIntToInt,
		addIntToInt,
		addIntToInt,
		addIntToInt,
		addIntToInt,
		addIntToInt,
		addIntToInt,
		addIntToInt,
		addIntToInt,
		addIntToInt,
		addIntToInt,
		addIntToInt,
		addIntToInt,
		addIntToInt,
		addIntToInt,
		addIntToInt,
		addIntToInt,
		addIntToInt,
		addIntToInt,
		addIntToInt,
		addFloatToFloat,
		addFloatToFloat,
		addFloatToFloat,
		addFloatToFloat
	};
	const usize IntrinsicOperatorCount = sizeof(intrinsicOperators) / sizeof(*intrinsicOperators);
}
