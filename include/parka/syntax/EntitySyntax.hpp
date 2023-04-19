#ifndef PARKA_SYNTAX_ENTITY_SYNTAX_HPP
#define PARKA_SYNTAX_ENTITY_SYNTAX_HPP

#include "parka/Token.hpp"
#include "parka/enum/EntityType.hpp"

namespace parka
{
	struct EntitySyntax
	{
		virtual ~EntitySyntax() {}

		virtual const String& identifier() const = 0;
		virtual EntityType type() const = 0;
	};
}

#endif
