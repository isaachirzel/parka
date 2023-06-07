#ifndef PARKA_CONTEXT_CONTEXT_TREE_HPP
#define PARKA_CONTEXT_CONTEXT_TREE_HPP

#include "parka/repository/EntityContextId.hpp"
#include "parka/syntax/SyntaxTree.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	class ContextTree
	{
		EntityContextId _globalPackageId;
		
		ContextTree(const EntityContextId& globalPackageId) :
		_globalPackageId(globalPackageId)
		{}

	public:

		ContextTree(ContextTree&&) = default;
		ContextTree(const ContextTree&) = default;

		static Optional<ContextTree> validate(const SyntaxTree& syntax);

		const auto& globalPackageId() const { return _globalPackageId; }
	};
}

#endif
