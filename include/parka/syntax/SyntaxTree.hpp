#ifndef PARKA_SYNTAX_AST_SYNTAX_HPP
#define PARKA_SYNTAX_AST_SYNTAX_HPP

#include "parka/syntax/ModuleSyntax.hpp"
#include "parka/syntax/PackageSyntax.hpp"
#include "parka/util/Project.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	class SyntaxTree
	{
		// TODO: Project metadata
		const PackageSyntax& _globalPackage;
		// TODO: External package ids

	private:

		SyntaxTree(const PackageSyntax& globalPackage) :
		_globalPackage(globalPackage)
		{}

	public:

		SyntaxTree(SyntaxTree&&) = default;
		SyntaxTree(const SyntaxTree&) = delete;

		static SyntaxTree parse(const Project& project);

		const auto& globalPackage() const { return _globalPackage; }
	};
}

#endif
