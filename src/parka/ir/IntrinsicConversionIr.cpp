#include "parka/ir/IntrinsicConversionIr.hpp"
#include "parka/ir/ConversionIr.hpp"
#include "parka/util/Float.hpp"
#include "parka/util/Integer.hpp"

namespace parka::ir
{
	IntrinsicConversionIr::IntrinsicConversionIr(const TypeIr& to, const TypeIr& from):
		ConversionIr(true),
		_to(to),
		_from(from)
	{}

	template <typename To, typename From>
	IntrinsicConversionIr conv()
	{
		const auto& to = TypeIr::of<To>();
		const auto& from = TypeIr::of<From>();

		return IntrinsicConversionIr(to, from);
	}

	IntrinsicConversionIr IntrinsicConversionIr::entries[] =
	{
		conv<void, Integer>(),
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
	const usize IntrinsicConversionIr::entryCount = sizeof(entries) / sizeof(*entries);
}
