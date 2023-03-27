#ifndef PARKA_ENTITY_HPP
#define PARKA_ENTITY_HPP

#include "parka/token.hpp"
#include "parka/entity/entity_id.hpp"

struct Entity
{
	virtual ~Entity() {}

	virtual Token token() const;
	virtual const String& symbol() const = 0;
	virtual EntityType type() const = 0;
};

#endif
