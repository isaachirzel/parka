#ifndef PARKA_ENTITY_LOCAL_ENTITY_HPP
#define PARKA_ENTITY_LOCAL_ENTITY_HPP

#include "parka/entity/entity.hpp"

class LocalEntity : public Entity
{
	virtual ~LocalEntity() {}

	virtual Token token() const = 0;
};

#endif
