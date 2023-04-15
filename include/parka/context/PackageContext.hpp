#ifndef PARKA_CONTEXT_PACKAGE_CONTEXT_HPP
#define PARKA_CONTEXT_PACKAGE_CONTEXT_HPP

#include "parka/repository/EntityContextId.hpp"
#include "parka/syntax/PackageSyntax.hpp"
#include "parka/util/Array.hpp"

namespace parka
{
	class PackageContext
	{
		Array<EntityContextId> _functionIds;
		Array<EntityContextId> _structIds;

		PackageContext(Array<EntityContextId>&& functionIds, Array<EntityContextId>&& structIds) :
		_functionIds(std::move(functionIds)),
		_structIds(std::move(structIds))
		{}

	public:

		static void validate(Array<EntityContextId>& packageIds, const EntitySyntaxId& syntax);
	};
}

#endif
