#ifndef PARKA_SYNTAX_AST_SYNTAX_HPP
#define PARKA_SYNTAX_AST_SYNTAX_HPP

#include "parka/data/EntityId.hpp"
#include "parka/Storage.hpp"
#include "parka/util/Project.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	class SyntaxTree
	{
		EntityId _globalPackageId;

		SyntaxTree(const EntityId& globalPackageId) :
		_globalPackageId(globalPackageId)
		{}

	public:

		SyntaxTree(SyntaxTree&&) = default;
		SyntaxTree(const SyntaxTree&) = delete;
		~SyntaxTree() = default;

		static Optional<SyntaxTree> parse(const Project& project);

		bool validate();
	};
}

#endif
