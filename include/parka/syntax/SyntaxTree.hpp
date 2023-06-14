#ifndef PARKA_SYNTAX_AST_SYNTAX_HPP
#define PARKA_SYNTAX_AST_SYNTAX_HPP

#include "parka/context/ContextTree.hpp"
#include "parka/enum/SymbolTableType.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/syntax/ModuleSyntax.hpp"
#include "parka/syntax/PackageSyntax.hpp"
#include "parka/util/Project.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	class SyntaxTree : public SymbolTable
	{
		// TODO: Project metadata
		PackageSyntax& _globalPackage;
		// TODO: External package ids
		
	public:

		SyntaxTree(PackageSyntax& globalPackage);
		SyntaxTree(SyntaxTree&&) = default;
		SyntaxTree(const SyntaxTree&) = delete;

		static SyntaxTree parse(const Project& project);

		bool declare(EntitySyntax& syntax);
		bool declareSelf();
		EntitySyntax *resolve(const Identifier& identifier);
		EntitySyntax *resolve(const QualifiedIdentifier& identifier);

		Optional<ContextTree> validate();

		SymbolTableType symbolTableType() const { return SymbolTableType::Global; }
		SymbolTable *parent() { return nullptr; }

		friend std::ostream& operator<<(std::ostream& out, const SyntaxTree& syntax);
	};
}

#endif
