#ifndef PARKA_SYNTAX_PACKAGE_SYNTAX_HPP
#define PARKA_SYNTAX_PACKAGE_SYNTAX_HPP

#include "parka/file/Directory.hpp"
#include "parka/symbol/Identifier.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/symbol/SymbolTableEntry.hpp"
#include "parka/ast/Entity.hpp"
#include "parka/ast/Module.hpp"

namespace parka
{
	class PackageContext : public EntityContext
	{
		Array<PackageContext*> _packages;
		Array<FunctionContext*> _functions;
		Array<StructContext*> _structs;

	public:

		PackageContext(Array<PackageContext*> packages, Array<FunctionContext*>&& functions, Array<StructContext*>&& structs);
		PackageContext(PackageContext&&) = default;
		PackageContext(const PackageContext&) = delete;

		EntityType entityType() const { return EntityType::Package; }
		const auto& packages() const { return _packages; }
		const auto& functions() const { return _functions; }
		const auto& structs() const { return _structs; }
	};

	class PackageSyntax : public EntitySyntax, public SymbolTable
	{
		String _name;
		Array<ModuleSyntax> _modules;
		Array<PackageSyntax*> _packages;
		// Symbol table data
		Table<String, EntitySyntax*> _symbols;
		PackageSyntax *_parent;
		PackageContext *_context;

	private:

		EntitySyntax *find(const Identifier& identifier);
		EntitySyntax *findAbsolute(const Identifier& identifier);

	public:

		PackageSyntax(String&& name, Array<ModuleSyntax>&& modules, Array<PackageSyntax*>&& packages);
		PackageSyntax(PackageSyntax&&) = default;
		PackageSyntax(const PackageSyntax&) = delete;

		static PackageSyntax *parse(const Directory& directory, const String& name);

		bool declare(EntitySyntax& entity);
		bool declareSelf(PackageSyntax *parent);
		EntitySyntax *resolve(const Identifier& identifier);
		EntitySyntax *resolve(const QualifiedIdentifier& identifier);

		PackageContext *validate();
		EntityContext *context() { return validate(); }
		
		SymbolTable *parent() { return _parent; }
		SymbolTableType symbolTableType() const { return SymbolTableType::Package; }
		EntityType entityType() const { return EntityType::Package; }
		const String& name() const { return _name; }
		const auto& modules() const { return _modules; }
		const auto& packages() const { return _packages; }

		friend std::ostream& operator<<(std::ostream& out, const PackageSyntax& package);
	};
}

#endif
