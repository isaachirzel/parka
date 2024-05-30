#ifndef PARKA_UTIL_TYPE_UTIL_HPP
#define PARKA_UTIL_TYPE_UTIL_HPP

#include "parka/ir/TypeIr.hpp"
#include "parka/ir/PrimitiveIr.hpp"
#include "parka/util/Float.hpp"
#include "parka/util/Integer.hpp"

namespace parka
{
	template <typename T>
	constexpr const ir::TypeIr& type()
	{
		if constexpr (std::is_same_v<T, Integer>)
			return ir::PrimitiveIr::integerPrimitive;

		if constexpr (std::is_same_v<T, Float>)
			return ir::PrimitiveIr::floatPrimitive;

		if constexpr (std::is_same_v<T, u8>)
			return ir::PrimitiveIr::u8Primitive;

		if constexpr (std::is_same_v<T, u16>)
			return ir::PrimitiveIr::u16Primitive;

		if constexpr (std::is_same_v<T, u32>)
			return ir::PrimitiveIr::u32Primitive;

		if constexpr (std::is_same_v<T, u64>)
			return ir::PrimitiveIr::u64Primitive;

		if constexpr (std::is_same_v<T, i8>)
			return ir::PrimitiveIr::i8Primitive;

		if constexpr (std::is_same_v<T, i16>)
			return ir::PrimitiveIr::i16Primitive;

		if constexpr (std::is_same_v<T, i32>)
			return ir::PrimitiveIr::i32Primitive;

		if constexpr (std::is_same_v<T, i64>)
			return ir::PrimitiveIr::i64Primitive;

		if constexpr (std::is_same_v<T, f32>)
			return ir::PrimitiveIr::f32Primitive;

		if constexpr (std::is_same_v<T, f64>)
			return ir::PrimitiveIr::f64Primitive;

		if constexpr (std::is_same_v<T, bool>)
			return ir::PrimitiveIr::boolPrimitive;

		if constexpr (std::is_same_v<T, char>)
			return ir::PrimitiveIr::charPrimitive;
	}
}

#endif
