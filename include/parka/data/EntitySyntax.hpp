#ifndef PARKA_ENTITY_HPP
#define PARKA_ENTITY_HPP

#include "parka/Token.hpp"
#include "parka/data/EntityId.hpp"

namespace parka
{
	struct EntitySyntax
	{
		virtual ~EntitySyntax() {}

		// virtual Token token() const = 0;
		// virtual const String& symbol() const = 0;
		virtual const String& identifier() const = 0;
		virtual EntityType type() const = 0;
	};
}

#endif
