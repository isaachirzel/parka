#ifndef PARKA_IR_ENTITY_HPP
#define PARKA_IR_ENTITY_HPP

#include "parka/enum/EntityType.hpp"
#include "parka/util/String.hpp"
#include "parka/ir/ValueType.hpp"

namespace parka::ir
{
	struct EntityIr
	{
		const EntityType entityType;

	public:

		EntityIr(EntityType entityType) :
		entityType(entityType)
		{}
		virtual ~EntityIr() {}
		virtual const String& symbol() const = 0;
		virtual const ValueType *valueType() const = 0;
	};
}

#endif
