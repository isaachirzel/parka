#ifndef PARKA_VALIDATOR_PACKAGE_VALIDATOR_HPP
#define PARKA_VALIDATOR_PACKAGE_VALIDATOR_HPP

#include "parka/ast/Function.hpp"
#include "parka/ast/Package.hpp"
#include "parka/ir/Function.hpp"
#include "parka/ir/Package.hpp"
#include "parka/symbol/Resolvable.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/symbol/FunctionSymbolTable.hpp"
#include "parka/util/Array.hpp"

namespace parka::validator
{
	class PackageSymbolTable: public SymbolTable, public Resolvable
	{
		const ast::PackageAst& _ast;
		String _scope;
		Table<String, Resolvable*> _symbols;
		Array<FunctionSymbolTable> _functions;
		PackageSymbolTable *_parent;
		ir::PackageIr *_ir;

	private:

		static String getScope(const ast::PackageAst& ast, PackageSymbolTable *parent);

	public:

		PackageSymbolTable(const ast::PackageAst& ast, PackageSymbolTable *parent = nullptr);

		bool declare(const Declarable& entity);
		// bool declareSelf(PackageSymbolTable *parent);
		Resolvable *find(const ast::Identifier& identifier);
		Resolvable *findInitial(const ast::Identifier& identifier);
		Resolvable *findAbsolute(const ast::Identifier& identifier);
		Resolution *resolve(const ast::QualifiedIdentifier& identifier);

		const auto& scope() const { return _scope; }
		const String& name() const { return _ast.name(); }
		auto& functions() { return _functions; }

		friend std::ostream& operator<<(std::ostream& out, const PackageSymbolTable& package);
	};
}

#endif
