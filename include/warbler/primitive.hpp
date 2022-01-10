#ifndef WARBLER_PRIMITIVE_HPP
#define WARBLER_PRIMITIVE_HPP

// standard headers
#include <cstdint>
#include <cstddef>
#include <string>
#include <string_view>

namespace warbler
{
	// unsigned integers

	using byte = uint8_t;
	using u8 = uint8_t;
	using u16 = uint16_t;
	using u32 = uint32_t;
	using u64 = uint64_t;
	using usize = size_t;

	// signed integers

	using i8 = int8_t;
	using i16 = int16_t;
	using i32 = int32_t;
	using i64 = int64_t;

	// floating point

	using f32 = float;
	using f64 = double;

	using String = std::string;
	using StringView = std::string_view;
}

#endif
