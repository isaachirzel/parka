#ifndef PARKA_ENTITY_HPP
#define PARKA_ENTITY_HPP

#include "parka/token.hpp"

enum class EntityType
{
	Package,
	Struct,
	Primitive,
	Function,
	Variable,
	Parameter
};

struct Entity
{
	virtual ~Entity() {}

	virtual Token token() const = 0;
	virtual const String& symbol() const = 0;
	virtual EntityType type() const = 0;
};

#endif
