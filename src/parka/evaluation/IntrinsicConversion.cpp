#include "parka/evaluation/IntrinsicConversion.hpp"
#include <cstring>

namespace parka::evaluation
{
	template <typename To, typename From>
	Value& _conv(Value& to, const Value& from)
	{
		auto f = *(const From*)from.value();
		auto t = (To)f;
		
		to.setValue(t);

		return to;
	}

	template <typename To, typename From>
	IntrinsicConversion conv()
	{
		return _conv<To, From>;
	}

	IntrinsicConversion intrinsicConversions[] =
	{
		conv<Integer, u8>(),
	};
	const usize intrinsicConversionCount = sizeof(intrinsicConversions) / sizeof(*intrinsicConversions);
}
