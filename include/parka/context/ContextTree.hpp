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
		
	public:

		static Optional<ContextTree> validate(const SyntaxTree&);
	};
}

#endif
