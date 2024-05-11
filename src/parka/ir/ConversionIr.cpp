#include "parka/ir/ConversionIr.hpp"
#include "parka/util/Float.hpp"
#include "parka/util/Integer.hpp"

namespace parka::ir
{
	template <typename From, typename To>
	ConversionIr conv()
	{
		const auto& from = Type::of<From>();
		const auto& to = Type::of<To>();

		return ConversionIr(from, to);
	}

	ConversionIr ConversionIr::entries[] =
	{
		conv<Integer, u8>(),
		conv<Integer, u16>(),
		conv<Integer, u32>(),
		conv<Integer, u64>(),
		conv<Integer, i8>(),
		conv<Integer, i16>(),
		conv<Integer, i32>(),
		conv<Integer, i64>(),
		conv<Float, f32>(),
		conv<Float, f64>()
	};
	const usize ConversionIr::entryCount = sizeof(entries) / sizeof(*entries);

	ConversionIr::ConversionIr(const Type& from, const Type& to):
		_from(from),
		_to(to)
	{}
}
