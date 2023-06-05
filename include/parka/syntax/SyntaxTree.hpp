#ifndef PARKA_SYNTAX_AST_SYNTAX_HPP
#define PARKA_SYNTAX_AST_SYNTAX_HPP

#include "parka/repository/EntitySyntaxId.hpp"
#include "parka/syntax/ModuleSyntax.hpp"
#include "parka/util/Project.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	class SyntaxTree
	{
		// TODO: Project metadata
		EntitySyntaxId _globalPackageId;
		// TODO: External package ids

	private:

		SyntaxTree(const EntitySyntaxId& packageId) :
		_globalPackageId(packageId)
		{}

	public:

		SyntaxTree(SyntaxTree&&) = default;
		SyntaxTree(const SyntaxTree&) = delete;

		static SyntaxTree parse(const Project& project);

		const auto& globalPackageId() const { return _globalPackageId; }
	};
}

#endif
