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
	void conv(FlatMap<ConversionKey, IntrinsicConversion>& conversions)
	{
		auto key = ConversionKey(ir::TypeIr::of<To>(), ir::TypeIr::of<From>());

		conversions.insert(key, _conv<To, From>);
	}

	FlatMap<ConversionKey, IntrinsicConversion> getIntrinsicConversions()
	{
		auto conversions = FlatMap<ConversionKey, IntrinsicConversion>(64);

		conv<u8, Integer>(conversions);
		conv<u16, Integer>(conversions);
		conv<u32, Integer>(conversions);
		conv<u64, Integer>(conversions);
		conv<i8, Integer>(conversions);
		conv<i16, Integer>(conversions);
		conv<i32, Integer>(conversions);
		conv<i64, Integer>(conversions);
		conv<f32, Float>(conversions);
		conv<f64, Float>(conversions);

		return conversions;
	}
}
