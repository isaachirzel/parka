#ifndef PARKA_SYNTAX_PACKAGE_SYNTAX_HPP
#define PARKA_SYNTAX_PACKAGE_SYNTAX_HPP

#include "parka/file/Directory.hpp"
#include "parka/ast/Identifier.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/ast/Entity.hpp"
#include "parka/ast/Module.hpp"

namespace parka
{
	class PackageContext : public EntityContext
	{
		String _symbol;
		Array<PackageContext*> _packages;
		Array<FunctionContext*> _functions;
		Array<StructContext*> _structs;

	public:

		PackageContext(String&& symbol, Array<PackageContext*> packages, Array<FunctionContext*>&& functions, Array<StructContext*>&& structs);
		PackageContext(PackageContext&&) = default;
		PackageContext(const PackageContext&) = delete;

		const String& symbol() const { return _symbol; }
		EntityType entityType() const { return EntityType::Package; }
		const auto& packages() const { return _packages; }
		const auto& functions() const { return _functions; }
		const auto& structs() const { return _structs; }
	};

	class PackageSyntax : public EntityEntry, public SymbolTable
	{
		String _name;
		Array<ModuleSyntax> _modules;
		Array<PackageSyntax*> _packages;
		Table<String, EntityEntry*> _symbols;
		PackageSyntax *_parent;
		PackageContext *_context;

	private:

		EntityEntry *find(const Identifier& identifier);
		EntityEntry *findAbsolute(const Identifier& identifier);

	public:

		PackageSyntax(String&& name, Array<ModuleSyntax>&& modules, Array<PackageSyntax*>&& packages);
		PackageSyntax(PackageSyntax&&) = default;
		PackageSyntax(const PackageSyntax&) = delete;

		static PackageSyntax *parse(const Directory& directory, const String& name);

		bool declare(EntitySyntax& entity);
		bool declareSelf(PackageSyntax *parent);
		EntityEntry *resolve(const Identifier& identifier);
		EntityEntry *resolve(const QualifiedIdentifier& identifier);
		String getSymbol() const;

		PackageContext *validate();
		EntityContext *context() { return validate(); }
		
		SymbolTableType symbolTableType() const { return SymbolTableType::Package; }
		EntityType entityType() const { return EntityType::Package; }
		const String& name() const { return _name; }
		const auto& modules() const { return _modules; }
		const auto& packages() const { return _packages; }

		friend std::ostream& operator<<(std::ostream& out, const PackageSyntax& package);
	};
}

#endif
