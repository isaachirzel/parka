#ifndef PARKA_SYNTAX_AST_SYNTAX_HPP
#define PARKA_SYNTAX_AST_SYNTAX_HPP

#include "parka/context/ContextTree.hpp"
#include "parka/syntax/ModuleSyntax.hpp"
#include "parka/syntax/PackageSyntax.hpp"
#include "parka/util/Project.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	class SyntaxTree
	{
		// TODO: Project metadata
		PackageSyntax& _globalPackage;
		// TODO: External package ids
		
	public:

		SyntaxTree(PackageSyntax& globalPackage);
		SyntaxTree(SyntaxTree&&) = default;
		SyntaxTree(const SyntaxTree&) = delete;

		static SyntaxTree parse(const Project& project);
		void declare();
		Optional<ContextTree> validate();

		friend std::ostream& operator<<(std::ostream& out, const SyntaxTree& syntax);
	};
}

#endif
