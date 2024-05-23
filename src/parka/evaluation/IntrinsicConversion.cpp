#include "parka/evaluation/IntrinsicConversion.hpp"
#include <cstring>

namespace parka::evaluation
{
	template <typename To, typename From>
	Value& _conv(Value& to, const Value& from)
	{
		auto f = from.getValue<From>();
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
		conv<u8, Integer>(),
		conv<u16, Integer>(),
		conv<u32, Integer>(),
		conv<u64, Integer>(),
		conv<i8, Integer>(),
		conv<i16, Integer>(),
		conv<i32, Integer>(),
		conv<i64, Integer>(),
		conv<f32, Float>(),
		conv<f64, Float>(),
	};
	const usize intrinsicConversionCount = sizeof(intrinsicConversions) / sizeof(*intrinsicConversions);
}
