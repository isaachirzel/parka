#ifndef PARKA_VALIDATION_RESOLVABLE_HPP
#define PARKA_VALIDATION_RESOLVABLE_HPP

#include "parka/enum/EntityType.hpp"
#include "parka/validation/Context.hpp"
#include "parka/util/String.hpp"
#include "parka/ir/EntityIr.hpp"

namespace parka::validation
{
	struct ContextEntry
	{
		const EntityType entityType;

	public:

		ContextEntry(EntityType entityType):
			entityType(entityType)
		{}
		virtual ~ContextEntry() {}

		virtual Context* context() = 0;
		virtual const String& name() const = 0;
		virtual ir::EntityIr *resolve() = 0;

		// TODO: be able to get snippet for errors

		friend std::ostream& operator<<(std::ostream& out, const ContextEntry& resolvabe);
	};
}

#endif
