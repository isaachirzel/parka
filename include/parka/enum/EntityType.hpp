#include "parka/util/Common.hpp"
#ifndef PARKA_ENUM_ENTITY_TYPE_HPP
#define PARKA_ENUM_ENTITY_TYPE_HPP

namespace parka
{
	enum class EntityType: u8
	{
		PackageSyntax,
		StructSyntax,
		Primitive,
		Function,
		Variable,
		ParameterSyntax
	};
}

#endif
