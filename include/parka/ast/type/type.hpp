#ifndef PARKA_TYPE_HPP
#define PARKA_TYPE_HPP

#include "parka/symbol/entity_id.hpp"
#include "parka/util/primitives.hpp"
#include "parka/util/string.hpp"

class Type
{
	EntityId _entityId;

	// TODO: Add pointer info
	// TODO: Add Literal for better type inference?
public:

	Type(EntityId entityId) :
	_entityId(entityId)
	{}
	Type(Type&&) = default;
	Type(const Type&) = default;
	~Type() = default;

	String getName() const;

	bool canConvertTo(const Type& other);

	const auto& entityId() const { return _entityId; }

	static const Type voidType;
	static const Type i32Type;
};

#endif