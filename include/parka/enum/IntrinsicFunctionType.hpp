#ifndef PARKA_ENUM_INTRINSIC_FUNCTION_TYPE_HPP
#define PARKA_ENUM_INTRINSIC_FUNCTION_TYPE_HPP

#include "parka/util/String.hpp"

namespace parka
{
	enum class IntrinsicFunctionType
	{
		Println
	};

	String symbolFromIntrinsicFunctionType(IntrinsicFunctionType intrinsicFunctionType);
}

#endif
