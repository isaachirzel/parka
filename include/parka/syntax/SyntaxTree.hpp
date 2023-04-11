#ifndef PARKA_SYNTAX_AST_SYNTAX_HPP
#define PARKA_SYNTAX_AST_SYNTAX_HPP

#include "parka/repository/EntitySyntaxId.hpp"
#include "parka/repository/Storage.hpp"
#include "parka/util/Project.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	class SyntaxTree
	{
		EntitySyntaxId _globalPackageId;

		SyntaxTree(const EntitySyntaxId& globalPackageId) :
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
