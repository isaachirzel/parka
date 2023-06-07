#ifndef PARKA_REPOSITORY_ENTITY_CONTEXT_HPP
#define PARKA_REPOSITORY_ENTITY_CONTEXT_HPP

#include "parka/enum/EntityType.hpp"

namespace parka
{
	struct EntityContext
	{
		virtual ~EntityContext() {}

		virtual EntityType type() const = 0;
	};
}

#endif
