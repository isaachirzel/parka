#ifndef PARKA_SYNTAX_AST_SYNTAX_HPP
#define PARKA_SYNTAX_AST_SYNTAX_HPP

#include "parka/enum/SymbolTableType.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/ast/Module.hpp"
#include "parka/ast/Package.hpp"
#include "parka/util/Project.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	class ContextTree
	{
		PackageContext& _globalPackage;
		
	public:

		ContextTree(PackageContext& globalPackage);
		ContextTree(ContextTree&&) = default;
		ContextTree(const ContextTree&) = default;
	};

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
		EntityEntry *resolve(const Identifier& identifier);
		EntityEntry *resolve(const QualifiedIdentifier& identifier);

		Optional<ContextTree> validate();

		SymbolTableType symbolTableType() const { return SymbolTableType::Global; }

		friend std::ostream& operator<<(std::ostream& out, const SyntaxTree& syntax);
	};
}

#endif
