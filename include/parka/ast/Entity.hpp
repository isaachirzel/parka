#ifndef PARKA_SYNTAX_ENTITY_SYNTAX_HPP
#define PARKA_SYNTAX_ENTITY_SYNTAX_HPP

#include "parka/ast/Identifier.hpp"

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

	struct EntityContext
	{
		virtual ~EntityContext() {}
		virtual EntityType entityType() const = 0;
		virtual const String& symbol() const = 0;
	};

	struct EntityEntry
	{
		virtual EntityType entityType() const = 0;
		virtual const String& name() const = 0;
		virtual EntityContext *context() = 0;

		friend std::ostream& operator<<(std::ostream& out, const EntityEntry &entry);
	};

	struct EntitySyntax : public EntityEntry
	{
		virtual ~EntitySyntax() {}
		virtual EntityType entityType() const = 0;
		virtual const Identifier& identifier() const = 0;
		virtual const String& name() const = 0;
		virtual EntityContext *context() = 0;

		// friend std::ostream& operator<<(std::ostream& out, const EntitySyntax& syntax);
	};

	
	std::ostream& operator<<(std::ostream& out, const EntityType& type);
}

#endif
