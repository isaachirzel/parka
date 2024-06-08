#ifndef PARKA_IR_L_VALUE_HPP
#define PARKA_IR_L_VALUE_HPP

#include "parka/enum/EntityType.hpp"
#include "parka/ir/TypeIr.hpp"
#include "parka/util/String.hpp"

namespace parka::ir
{
	struct EntityIr
	{
		const EntityType entityType;

		EntityIr(EntityType entityType):
			entityType(entityType)
		{}

		virtual ~EntityIr() {}

		virtual const TypeIr& type() const = 0;
		virtual const String& symbol() const = 0;
	};
}

#endif
