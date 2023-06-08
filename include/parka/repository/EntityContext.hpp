#ifndef PARKA_REPOSITORY_ENTITY_CONTEXT_HPP
#define PARKA_REPOSITORY_ENTITY_CONTEXT_HPP

#include "parka/enum/EntityType.hpp"
#include "parka/repository/EntityContextId.hpp"

namespace parka
{
	struct EntityContext
	{
		virtual ~EntityContext() {}

		virtual EntityType type() const = 0;

		static const EntityContext& create(EntityContext&& context);
		static const EntityContext& get(const EntityContextId& id);
		static EntityContextId idFor(const EntityContext& context);
	};
}

#endif
