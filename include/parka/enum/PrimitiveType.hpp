#ifndef PARKA_ENUM_PRIMITIVE_TYPE_HPP
#define PARKA_ENUM_PRIMITIVE_TYPE_HPP

#include "parka/util/Common.hpp"

#include <ostream>

namespace parka
{
	enum class PrimitiveType: u8
	{
		Void,
		Integer,
		U8,
		U16,
		U32,
		U64,
		I8,
		I16,
		I32,
		I64,
		Float,
		F32,
		F64,
		Bool,
		Char,
		String
	};
	
	std::ostream& operator<<(std::ostream& out, const PrimitiveType& primitiveType);
}

#endif
