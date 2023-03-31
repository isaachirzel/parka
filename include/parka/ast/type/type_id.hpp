#ifndef PARKA_AST_TYPE_TYPE_ID_HPP
#define PARKA_AST_TYPE_TYPE_ID_HPP

#include "parka/symbol/entity_id.hpp"
#include "parka/util/primitives.hpp"
#include <cassert>

class TypeId
{
	EntityType _entityType;
	usize _index;

public:

	TypeId(EntityType entityType, usize index) :
	_entityType(entityType),
	_index(index)
	{
		assert(entityType == EntityType::Struct || entityType == EntityType::Primitive);
	}
	TypeId(TypeId&&) = default;
	TypeId(const TypeId&) = default;
	~TypeId() = default;

	const auto& entityType() const { return _entityType; }
	const auto& index() const { return _index; }
}

#endif