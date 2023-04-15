#ifndef PARKA_CONTEXT_CONTEXT_TREE_HPP
#define PARKA_CONTEXT_CONTEXT_TREE_HPP

#include "parka/repository/EntityContextId.hpp"
#include "parka/syntax/SyntaxTree.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	class ContextTree
	{
		Array<EntityContextId> _packageIds;
		
		ContextTree(Array<EntityContextId>&& packageIds) :
		_packageIds(std::move(packageIds))
		{}

	public:

		static Optional<ContextTree> validate(const SyntaxTree&);
	};
}

#endif
