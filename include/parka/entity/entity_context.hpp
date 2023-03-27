#ifndef PARKA_ENTITY_CONTEXT_HPP
#define PARKA_ENTITY_CONTEXT_HPP

#include "parka/entity/entity.hpp"

#include <cstdint>

enum class ValidationStatus
{
	Pending,
	Invalid,
	Valid
};

class EntityContext
{
	// EntityId _entityId;
	Entity& _entity;
	EntityId _entityId;
	ValidationStatus _status;
	// read count?
	// write count?

public:

	EntityContext(Entity& entity, EntityId entityId) :
	_entity(entity),
	_entityId(entityId),
	_status(ValidationStatus::Pending)
	{}
	EntityContext(EntityContext&&) = default;
	EntityContext(const EntityContext&) = delete;
	~EntityContext() = default;

	void invalidate() { _status = ValidationStatus::Invalid; }
	void validate() { _status = ValidationStatus::Valid; }

	const auto& entityId() const { return _entityId; }
	const auto& symbol() const { return _entity.symbol(); }
	const auto& entity() const { return _entity; }
	const auto& status() const { return _status; }
};

String entityTypeGetName(EntityType type);

#endif
