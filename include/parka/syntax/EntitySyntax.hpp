#ifndef PARKA_SYNTAX_ENTITY_SYNTAX_HPP
#define PARKA_SYNTAX_ENTITY_SYNTAX_HPP

#include "parka/enum/EntityType.hpp"
#include "parka/repository/EntitySyntaxId.hpp"
#include "parka/util/String.hpp"

namespace parka
{
	struct EntitySyntax
	{
		virtual ~EntitySyntax() {}

		virtual const String& identifier() const = 0;
		virtual EntityType type() const = 0;

		static const EntitySyntax& create(EntitySyntax&& syntax);
		static const EntitySyntax& get(const EntitySyntaxId& id);
		static EntitySyntaxId idFor(const EntitySyntax& syntax);
	};
}

#endif
