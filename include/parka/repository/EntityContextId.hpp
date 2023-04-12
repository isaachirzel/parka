#ifndef PARKA_REPOSITORY_ENTITY_CONTEXT_ID_HPP
#define PARKA_REPOSITORY_ENTITY_CONTEXT_ID_HPP

#include "parka/enum/EntityType.hpp"
#include "parka/util/Common.hpp"

namespace parka
{
	class EntityContextId
	{
		EntityType _type;
		usize _index;

		EntityContextId(EntityType type, usize index) :
		_type(type),
		_index(index)
		{}

	public:

		EntityContextId(EntityContextId&&) = default;
		EntityContextId(const EntityContextId&) = default;
		~EntityContextId() = default;

		const auto& type() const { return _type; }
		const auto& index() const { return _index; }

		friend struct ContextRepository;
	};
};

#endif
