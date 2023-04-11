#ifndef PARKA_ENTITY_ENTITY_ID_HPP
#define PARKA_ENTITY_ENTITY_ID_HPP

#include "parka/util/Primitives.hpp"
#include <ostream>

namespace parka
{
	enum class EntityType: u8
	{
		PackageSyntax,
		StructSyntax,
		Primitive,
		Function,
		Variable,
		ParameterSyntax
	};

	class EntityId
	{
		u32 _index;
		EntityType _type;

		EntityId(EntityType type, usize index) :
		_index(index),
		_type(type)
		{}

	public:

		EntityId(EntityId&&) = default;
		EntityId(const EntityId&) = default;
		~EntityId() = default;
		EntityId& operator=(EntityId&& other) = default;
		EntityId& operator=(const EntityId& other) = default;

		const auto& index() const { return _index; }
		const auto& type() const { return _type; }

		friend std::ostream& operator<<(std::ostream& out, const EntityId& id);
		bool operator==(const EntityId& other) const;

		friend struct Storage;
	};

	std::ostream& operator<<(std::ostream& out, const EntityType& type);
}

#endif
