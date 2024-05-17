#ifndef PARKA_ENUM_PRIMITIVE_TYPE_HPP
#define PARKA_ENUM_PRIMITIVE_TYPE_HPP

#include "parka/util/Common.hpp"

namespace parka
{
	enum class PrimitiveType: u8
	{
		Void,
		UnsignedInteger,
		SignedInteger,
		FloatingPoint,
		Boolean,
		Character,
		String
	};
}

#endif
