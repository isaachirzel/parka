#include "parka/ir/ConversionIr.hpp"
#include "parka/util/Float.hpp"
#include "parka/util/Integer.hpp"

namespace parka::ir
{
	template <typename To, typename From>
	void conv(FlatMap<ConversionKey, ConversionIr*>& conversions)
	{
		const auto& to = TypeIr::of<To>();
		const auto& from = TypeIr::of<From>();

		auto key = ConversionKey(to, from);
		auto* conversion = new ConversionIr(to, from);

		conversions.insert(key, conversion);
	}

	template <typename To, typename From>
	ConversionKey key()
	{
		return ConversionKey(TypeIr::of<To>(), TypeIr::of<From>());
	}

	FlatMap<ConversionKey, ConversionIr*> ConversionIr::getIntrinsicConversions()
	{
		auto conversions = FlatMap<ConversionKey, ConversionIr*>(64);

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

	ConversionIr::ConversionIr(const TypeIr& to, const TypeIr& from):
		_to(to),
		_from(from)
	{}
}
