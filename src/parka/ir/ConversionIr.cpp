#include "parka/ir/ConversionIr.hpp"

namespace parka::ir
{
	template <typename From, typename To>
	ConversionIr conv()
	{
		const auto& from = Type::of<From>();
		const auto& to = Type::of<From>();

		return ConversionIr(from, to);
	}

	template <typename To>
	ConversionIr integerConv()
	{
		const auto& to = Type::of<To>();

		return ConversionIr(Type::integerType, to);
	}

	template <typename To>
	ConversionIr floatConv()
	{
		const auto& to = Type::of<To>();

		return ConversionIr(Type::integerType, to);
	}

	ConversionIr ConversionIr::entries[] =
	{
		integerConv<u8>(),
		integerConv<u16>(),
		integerConv<u32>(),
		integerConv<u64>(),
		integerConv<i8>(),
		integerConv<i16>(),
		integerConv<i32>(),
		integerConv<i64>(),
		floatConv<f32>(),
		floatConv<f64>(),
	};
	const usize ConversionIr::entryCount = sizeof(entries) / sizeof(*entries);

	ConversionIr::ConversionIr(const Type& from, const Type& to):
		_from(from),
		_to(to)
	{}
}
