#ifndef PARKA_VALIDATOR_PACKAGE_VALIDATOR_HPP
#define PARKA_VALIDATOR_PACKAGE_VALIDATOR_HPP

#include "parka/ast/Function.hpp"
#include "parka/ast/Package.hpp"
#include "parka/ir/Function.hpp"
#include "parka/ir/Package.hpp"
#include "parka/symbol/Resolvable.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/symbol/FunctionEntry.hpp"
#include "parka/util/Array.hpp"

namespace parka
{
	class PackageSymbolTable: public SymbolTable
	{
		String _scope;
		Table<String, Resolvable*> _symbols;
		Array<FunctionEntry> _functions;
		// Array<StructSymbolTable> _structs;
		PackageSymbolTable *_parent;

	public:

		PackageSymbolTable(const ast::PackageAst& ast, PackageSymbolTable *parent = nullptr);

		Resolvable *find(const ast::Identifier& identifier);
		Resolvable *findInitial(const ast::Identifier& identifier);
		Resolvable *findAbsolute(const ast::Identifier& identifier);
		Resolution *resolve(const ast::QualifiedIdentifier& identifier);

		const String& scope() const { return _scope; }
		auto& functions() { return _functions; }

		friend std::ostream& operator<<(std::ostream& out, const PackageSymbolTable& package);
	};
}

#endif
