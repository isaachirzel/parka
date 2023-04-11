#ifndef PARKA_REPOSITORY_ENTITY_CONTEXT_ID_HPP
#define PARKA_REPOSITORY_ENTITY_CONTEXT_ID_HPP

#include "parka/enum/EntityType.hpp"
#include "parka/util/Primitives.hpp"

namespace parka
{
	class EntityContextId
	{
		EntityType _type;
		usize _index;

	public:

		const auto& type() const { return _type; }
		const auto& index() const { return _index; }
	};
};

#endif
