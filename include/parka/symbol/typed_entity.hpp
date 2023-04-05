#ifndef PARKA_SYMBOL_TYPED_ENTITY_HPP
#define PARKA_SYMBOL_TYPED_ENTITY_HPP

#include "parka/ast/type/type.hpp"
#include "parka/symbol/entity.hpp"
#include "parka/util/optional.hpp"

struct TypedEntity : public Entity
{
	virtual ~TypedEntity() {}

	virtual Optional<Type> getType() const = 0;
};

#endif
