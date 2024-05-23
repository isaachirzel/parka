#ifndef PARKA_ENUM_PREFIX_TYPE_HPP
#define PARKA_ENUM_PREFIX_TYPE_HPP

#include "parka/util/Common.hpp"

namespace parka
{
	enum class PrefixType: u8
	{
		Reference,
		Dereference,
		Positive,
		Negative,
		BitwiseNot,
		BooleanNot
	};
}

#endif
