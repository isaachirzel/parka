#include "parka/evaluation/IntegerValue.hpp"

namespace parka::evaluation
{
	Value& IntegerValue::add(const Value& other) const
	{
		const auto& integer = dynamic_cast<const IntegerValue&>(other);
		auto value = _value + integer.value();
		auto *result = new IntegerValue(_type, value);
		// TODO: Handle memory leak
		return *result;
	}
}
