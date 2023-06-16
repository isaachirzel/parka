#ifndef PARKA_ENUM_ENTITY_TYPE_HPP
#define PARKA_ENUM_ENTITY_TYPE_HPP

#include "parka/util/Common.hpp"

namespace parka
{
	enum class EntityType: u8
	{
		Package,
		Struct,
		Primitive,
		Function,
		Variable,
		Parameter,
		Member
	};

	std::ostream& operator<<(std::ostream& out, const EntityType& type);
}

#endif
