#ifndef PARKA_ENTITY_ENTITY_ID_HPP
#define PARKA_ENTITY_ENTITY_ID_HPP

#include "parka/util/primitives.hpp"

enum class EntityType
{
	Package,
	Struct,
	Primitive,
	Function,
	Variable,
	Parameter
};

class EntityId
{
	usize _index;
	EntityType _type;

public:

	EntityId() :
	EntityId(EntityType::Package, SIZE_MAX)
	{}
	EntityId(EntityType type, usize index) :
	_index(index),
	_type(type)
	{}
	EntityId(EntityId&&) = default;
	EntityId(const EntityId&) = default;
	~EntityId() = default;
	EntityId& operator=(EntityId&& other) = default;
	EntityId& operator=(const EntityId& other) = default;

	const auto& index() const { return _index; }
	const auto& type() const { return _type; }

	bool operator==(const EntityId& other) const
	{
		return _type == other.type() && _index == other.index();
	}
};

#endif
