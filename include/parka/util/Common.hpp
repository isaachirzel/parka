#ifndef PARKA_UTIL_COMMON_HPP
#define PARKA_UTIL_COMMON_HPP

// standard headers
#include <cassert>
#include <cstdint>
#include <cstddef>
#include <functional>

namespace parka
{
	// unsigned integers
	using byte = uint8_t;
	using u8 = uint8_t;
	using u16 = uint16_t;
	using u32 = uint32_t;
	using u64 = uint64_t;
	using usize = uintptr_t;
	using isize = intptr_t;

	// signed integers
	using i8 = int8_t;
	using i16 = int16_t;
	using i32 = int32_t;
	using i64 = int64_t;

	// floating point
	using f32 = float;
	using f64 = double;
}

#endif
