#include "parka/context/ContextTree.hpp"
#include "parka/context/PackageContext.hpp"
#include "parka/log/Log.hpp"
#include "parka/repository/EntityContextId.hpp"
#include "parka/repository/EntitySyntaxId.hpp"
#include "parka/symbol/PackageSymbolTable.hpp"
#include "parka/symbol/SymbolTableEntry.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	Optional<ContextTree> ContextTree::validate(const SyntaxTree& tree)
	{
		auto symbolTable = PackageSymbolTable(tree.globalPackageId(), nullptr);

		std::cout << symbolTable << std::endl;

		return {};
		// auto packageIds = Array<EntityContextId>(8);

		// for (const auto&  : syntax.packageIds())
		// {
		// 	// PackageContext::validate(packageIds, syntax.globalPackageId());
		// }

		
		// auto context = ContextTree(std::move(packageIds));

		// return context;
	}
}
