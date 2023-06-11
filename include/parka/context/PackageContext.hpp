#ifndef PARKA_CONTEXT_PACKAGE_CONTEXT_HPP
#define PARKA_CONTEXT_PACKAGE_CONTEXT_HPP

#include "parka/context/FunctionContext.hpp"
#include "parka/context/StructContext.hpp"
#include "parka/repository/EntityContext.hpp"
#include "parka/repository/EntityContextId.hpp"
#include "parka/util/Array.hpp"

namespace parka
{
	class PackageContext : public EntityContext
	{
		Array<PackageContext*> _packages;
		Array<FunctionContext*> _functions;
		Array<StructContext*> _structs;

	public:

		PackageContext(Array<PackageContext*> packages, Array<FunctionContext*>&& functions, Array<StructContext*>&& structs);
		PackageContext(PackageContext&&) = default;
		PackageContext(const PackageContext&) = delete;

		EntityType entityType() const { return EntityType::Package; }
	};
}

#endif
