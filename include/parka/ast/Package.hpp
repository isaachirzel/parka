#ifndef PARKA_AST_PACKAGE_HPP
#define PARKA_AST_PACKAGE_HPP

#include "parka/enum/EntityType.hpp"
#include "parka/file/Directory.hpp"
#include "parka/ast/Identifier.hpp"
#include "parka/ir/Package.hpp"
#include "parka/symbol/Resolvable.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/ast/Module.hpp"

namespace parka::ast
{
	class PackageAst : public Resolvable, public SymbolTable
	{
		String _name;
		Array<ModuleAst> _modules;
		Array<PackageAst*> _packages;
		Table<String, Resolvable*> _symbols;
		PackageAst *_parent;
		ir::PackageIr *_context;

	public:

		PackageAst(String&& identifier, Array<ModuleAst>&& modules, Array<PackageAst*>&& packages) :
		Resolvable(ResolvableType::Package),
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

		bool declare(Declarable& declarable);
		bool declareSelf(PackageAst *parent);
		Resolvable *find(const Identifier& identifier);
		Resolvable *findInitial(const Identifier& identifier);
		Resolvable *findAbsolute(const Identifier& identifier);
		Resolution *resolve(const QualifiedIdentifier& identifier);
		String getSymbol() const;
		
		const String& name() const { return _name; }
		const auto& modules() const { return _modules; }
		const auto& packages() const { return _packages; }

		friend std::ostream& operator<<(std::ostream& out, const PackageAst& package);
	};
}

#endif
