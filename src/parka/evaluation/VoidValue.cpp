#include "parka/evaluation/VoidValue.hpp"

namespace parka::evaluation
{
	Value& VoidValue::add(const Value&) const
	{
		auto *result = new VoidValue();

		return *result;
	}
}
