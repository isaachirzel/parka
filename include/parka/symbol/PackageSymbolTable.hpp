#ifndef PARKA_SYMBOL_PACKAGE_SYMBOL_TABLE_HPP
#define PARKA_SYMBOL_PACKAGE_SYMBOL_TABLE_HPP

#include "parka/ast/PackageAst.hpp"
#include "parka/ir/FunctionIr.hpp"
#include "parka/ir/LValueIr.hpp"
#include "parka/symbol/Resolvable.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/symbol/FunctionEntry.hpp"
#include "parka/util/Array.hpp"
#include "parka/util/Table.hpp"

namespace parka
{
	class PackageSymbolTable: public SymbolTable
	{
		String _scope;
		Table<String, Resolvable*> _symbols;
		Array<ir::OperatorIr*> _operators;
		Array<FunctionEntry> _functions;
		// Array<StructSymbolTable> _structs;
		PackageSymbolTable *_parent;

	public:

		PackageSymbolTable(const ast::PackageAst& ast, PackageSymbolTable *parent = nullptr);

		Resolvable *find(const ast::Identifier& identifier);
		Resolvable *findInitial(const ast::Identifier& identifier);
		Resolvable *findAbsolute(const ast::Identifier& identifier);
		ir::LValueIr *resolve(const ast::QualifiedIdentifier& identifier);
		ir::OperatorIr *resolve(OperatorType type, const ir::Type& left, const ir::Type *right);
		ir::ConversionIr *resolveConversion(const ir::Type& from, const ir::Type& to);

		const String& scope() const { return _scope; }
		auto& functions() { return _functions; }

		friend std::ostream& operator<<(std::ostream& out, const PackageSymbolTable& package);
	};
}

#endif
