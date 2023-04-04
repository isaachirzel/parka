#ifndef PARKA_ENTITY_HPP
#define PARKA_ENTITY_HPP

#include "parka/token.hpp"
#include "parka/symbol/entity_id.hpp"

struct Entity
{
	virtual ~Entity() {}

	// virtual Token token() const = 0;
	// virtual const String& symbol() const = 0;
	virtual const String& identifier() const = 0;
	virtual EntityType type() const = 0;
};

#endif
