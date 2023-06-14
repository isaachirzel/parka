#ifndef PARKA_SYNTAX_PACKAGE_SYNTAX_HPP
#define PARKA_SYNTAX_PACKAGE_SYNTAX_HPP

#include "parka/context/PackageContext.hpp"
#include "parka/file/Directory.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/symbol/SymbolTableEntry.hpp"
#include "parka/syntax/EntitySyntax.hpp"
#include "parka/syntax/ModuleSyntax.hpp"

namespace parka
{
	class PackageSyntax : public EntitySyntax, public SymbolTable
	{
		String _identifier;
		Array<ModuleSyntax> _modules;
		Array<PackageSyntax*> _packages;
		// Symbol table data
		Table<String, EntitySyntax*> _symbols;
		PackageSyntax *_parent;
		PackageContext *_context;

	private:

		EntitySyntax *find(const String& key);

	public:

		PackageSyntax(String&& identifier, Array<ModuleSyntax>&& modules, Array<PackageSyntax*>&& packages);
		PackageSyntax(PackageSyntax&&) = default;
		PackageSyntax(const PackageSyntax&) = delete;

		static PackageSyntax *parse(const Directory& directory, const String& name);

		bool declare(EntitySyntax& entity);
		bool declareSelf(PackageSyntax *parent);
		EntitySyntax *resolve(const Identifier& identifier);
		EntitySyntax *resolve(const QualifiedIdentifier& identifier);

		PackageContext *validate();
		
		SymbolTable *parent() { return _parent; }
		SymbolTableType symbolTableType() const { return SymbolTableType::Package; }
		EntityType entityType() const { return EntityType::Package; }
		const String& identifier() const { return _identifier; }
		const auto& modules() const { return _modules; }
		const auto& packages() const { return _packages; }

		friend std::ostream& operator<<(std::ostream& out, const PackageSyntax& package);
	};
}

#endif
