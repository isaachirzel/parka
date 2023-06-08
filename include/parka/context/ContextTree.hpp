#ifndef PARKA_CONTEXT_CONTEXT_TREE_HPP
#define PARKA_CONTEXT_CONTEXT_TREE_HPP

#include "parka/context/PackageContext.hpp"
#include "parka/repository/EntityContextId.hpp"
#include "parka/syntax/SyntaxTree.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	class ContextTree
	{
		const PackageContext& _globalPackageId;
		
	private:

		ContextTree(const PackageContext& globalPackageId) :
		_globalPackageId(globalPackageId)
		{}

	public:

		ContextTree(ContextTree&&) = default;
		ContextTree(const ContextTree&) = default;

		static Optional<ContextTree> validate(const SyntaxTree& syntax);

		const auto& globalPackage() const { return _globalPackageId; }
	};
}

#endif
