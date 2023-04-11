#ifndef PARKA_ENTITY_ENTITY_ID_HPP
#define PARKA_ENTITY_ENTITY_ID_HPP

#include "parka/enum/EntityType.hpp"
#include "parka/util/Primitives.hpp"

#include <ostream>

namespace parka
{
	class EntitySyntaxId
	{
		u32 _index;
		EntityType _type;

		EntitySyntaxId(EntityType type, usize index) :
		_index(index),
		_type(type)
		{}

	public:

		EntitySyntaxId(EntitySyntaxId&&) = default;
		EntitySyntaxId(const EntitySyntaxId&) = default;
		~EntitySyntaxId() = default;
		EntitySyntaxId& operator=(EntitySyntaxId&& other) = default;
		EntitySyntaxId& operator=(const EntitySyntaxId& other) = default;

		const auto& index() const { return _index; }
		const auto& type() const { return _type; }

		friend std::ostream& operator<<(std::ostream& out, const EntitySyntaxId& id);
		bool operator==(const EntitySyntaxId& other) const;

		friend struct Storage;
	};

	std::ostream& operator<<(std::ostream& out, const EntityType& type);
}

#endif
