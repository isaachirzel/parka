#ifndef PARKA_CONTEXT_CONTEXT_TREE_HPP
#define PARKA_CONTEXT_CONTEXT_TREE_HPP

#include "parka/context/PackageContext.hpp"
#include "parka/repository/EntityContextId.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	class ContextTree
	{
		PackageContext& _globalPackage;
		
	public:

		ContextTree(PackageContext& globalPackage);
		ContextTree(ContextTree&&) = default;
		ContextTree(const ContextTree&) = default;
	};
}

#endif
