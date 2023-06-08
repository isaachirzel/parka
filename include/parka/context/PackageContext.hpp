#ifndef PARKA_CONTEXT_PACKAGE_CONTEXT_HPP
#define PARKA_CONTEXT_PACKAGE_CONTEXT_HPP

#include "parka/repository/EntityContext.hpp"
#include "parka/repository/EntityContextId.hpp"
#include "parka/symbol/PackageSymbolTable.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/syntax/PackageSyntax.hpp"
#include "parka/util/Array.hpp"

namespace parka
{
	class PackageContext : public EntityContext
	{
		Array<EntityContextId> _packageIds;
		Array<EntityContextId> _functionIds;
		Array<EntityContextId> _structIds;

		PackageContext(Array<EntityContextId>&& functionIds, Array<EntityContextId>&& structIds) :
		_functionIds(std::move(functionIds)),
		_structIds(std::move(structIds))
		{}

	public:

		static const PackageContext *validate(PackageSymbolTable& symbols);

		EntityType type() const { return EntityType::Package; }
	};
}

#endif
