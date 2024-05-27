#ifndef PARKA_UTIL_TYPE_UTIL_HPP
#define PARKA_UTIL_TYPE_UTIL_HPP

#include "parka/ir/BoolPrimitiveIr.hpp"
#include "parka/ir/CharPrimitiveIr.hpp"
#include "parka/ir/F32PrimitiveIr.hpp"
#include "parka/ir/F64PrimitiveIr.hpp"
#include "parka/ir/FloatPrimitiveIr.hpp"
#include "parka/ir/I16PrimitiveIr.hpp"
#include "parka/ir/I32PrimitiveIr.hpp"
#include "parka/ir/I64PrimitiveIr.hpp"
#include "parka/ir/I8PrimitiveIr.hpp"
#include "parka/ir/IntegerPrimitiveIr.hpp"
#include "parka/ir/TypeIr.hpp"
#include "parka/ir/U16PrimitiveIr.hpp"
#include "parka/ir/U32PrimitiveIr.hpp"
#include "parka/ir/U64PrimitiveIr.hpp"
#include "parka/ir/U8PrimitiveIr.hpp"
#include "parka/util/Float.hpp"
#include "parka/util/Integer.hpp"

namespace parka
{
	template <typename T>
	constexpr const ir::TypeIr& type()
	{
		if constexpr (std::is_same_v<T, Integer>)
			return ir::IntegerPrimitiveIr::instance;

		if constexpr (std::is_same_v<T, Float>)
			return ir::FloatPrimitiveIr::instance;

		if constexpr (std::is_same_v<T, u8>)
			return ir::U8PrimitiveIr::instance;

		if constexpr (std::is_same_v<T, u16>)
			return ir::U16PrimitiveIr::instance;

		if constexpr (std::is_same_v<T, u32>)
			return ir::U32PrimitiveIr::instance;

		if constexpr (std::is_same_v<T, u64>)
			return ir::U64PrimitiveIr::instance;

		if constexpr (std::is_same_v<T, i8>)
			return ir::I8PrimitiveIr::instance;

		if constexpr (std::is_same_v<T, i16>)
			return ir::I16PrimitiveIr::instance;

		if constexpr (std::is_same_v<T, i32>)
			return ir::I32PrimitiveIr::instance;

		if constexpr (std::is_same_v<T, i64>)
			return ir::I64PrimitiveIr::instance;

		if constexpr (std::is_same_v<T, f32>)
			return ir::F32PrimitiveIr::instance;

		if constexpr (std::is_same_v<T, f64>)
			return ir::F64PrimitiveIr::instance;

		if constexpr (std::is_same_v<T, bool>)
			return ir::BoolPrimitiveIr::instance;

		if constexpr (std::is_same_v<T, char>)
			return ir::CharPrimitiveIr::instance;
	}
}

#endif
