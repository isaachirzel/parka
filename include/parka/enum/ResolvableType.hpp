#ifndef PARKA_ENUM_RESOLVABLE_TYPE_HPP
#define PARKA_ENUM_RESOLVABLE_TYPE_HPP

#include "parka/util/Common.hpp"

namespace parka
{
	enum class ResolvableType: u8
	{
		Package,
		Primitive,
		Struct,
		Function,
		IntrinsicFunction,
		Variable,
		Parameter,
		Member
	};

	std::ostream& operator<<(std::ostream& out, const ResolvableType& type);
}

#endif
