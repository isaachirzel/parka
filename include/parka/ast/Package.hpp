#ifndef PARKA_AST_PACKAGE_HPP
#define PARKA_AST_PACKAGE_HPP

#include "parka/enum/EntityType.hpp"
#include "parka/file/Directory.hpp"
#include "parka/ast/Identifier.hpp"
#include "parka/ir/Entity.hpp"
#include "parka/ir/Package.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/ast/Entity.hpp"
#include "parka/ast/Module.hpp"

namespace parka::ast
{
	class PackageAst : public SymbolTableEntry, public SymbolTable
	{
		String _name;
		Array<ModuleAst> _modules;
		Array<PackageAst*> _packages;
		Table<String, SymbolTableEntry*> _symbols;
		PackageAst *_parent;
		ir::PackageIr *_context;

	public:

		PackageAst(String&& identifier, Array<ModuleAst>&& modules, Array<PackageAst*>&& packages) :
		SymbolTableEntry(SymbolTableEntryType::Package),
		SymbolTable(SymbolTableType::Package),
		_name(std::move(identifier)),
		_modules(std::move(modules)),
		_packages(std::move(packages)),
		_symbols(),
		_parent(nullptr),
		_context(nullptr)
		{}
		PackageAst(PackageAst&&) = default;
		PackageAst(const PackageAst&) = delete;

		static PackageAst *parse(const Directory& directory, const String& name);

		bool declare(EntityAst& entity);
		bool declareSelf(PackageAst *parent);
		SymbolTableEntry *find(const Identifier& identifier);
		SymbolTableEntry *findInitial(const Identifier& identifier);
		SymbolTableEntry *findAbsolute(const Identifier& identifier);
		ir::EntityIr *resolve(const QualifiedIdentifier& identifier);
		String getSymbol() const;

		ir::PackageIr *validate();
		// ir::EntityIr *context() { return validate(); }
		
		const String& name() const { return _name; }
		const auto& modules() const { return _modules; }
		const auto& packages() const { return _packages; }

		friend std::ostream& operator<<(std::ostream& out, const PackageAst& package);
	};
}

#endif
