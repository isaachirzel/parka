#include "parka/context/ContextTree.hpp"
#include "parka/context/PackageContext.hpp"
#include "parka/repository/EntityContextId.hpp"
#include "parka/repository/EntitySyntaxId.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	Optional<ContextTree> ContextTree::validate(const SyntaxTree& syntax)
	{
		auto packageIds = Array<EntityContextId>(8);

		PackageContext::validate(packageIds, syntax.globalPackageId());
		
		auto context = ContextTree(std::move(packageIds));

		return context;
	}
}
