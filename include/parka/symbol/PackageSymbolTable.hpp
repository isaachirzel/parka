#ifndef PARKA_SYMBOL_PACKAGE_SYMBOL_TABLE_HPP
#define PARKA_SYMBOL_PACKAGE_SYMBOL_TABLE_HPP

#include "parka/ast/PackageAst.hpp"
#include "parka/ir/ConversionIr.hpp"
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
		Array<ir::ConversionIr*> _conversions;
		Array<FunctionEntry> _functions;
		PackageSymbolTable *_parent;

	public:

		PackageSymbolTable(const ast::PackageAst& ast, PackageSymbolTable *parent = nullptr);

		Resolvable *findSymbol(const ast::Identifier& identifier);
		Resolvable *findInitialSymbol(const ast::Identifier& identifier);
		Resolvable *findAbsoluteSymbol(const ast::Identifier& identifier);
		ir::LValueIr *resolveSymbol(const ast::QualifiedIdentifier& identifier);
		ir::OperatorIr *resolveBinaryOperator(OperatorType type, const ir::Type& left, const ir::Type *right);
		ir::ConversionIr *resolveConversion(const ir::Type& from, const ir::Type& to);

		const String& scope() const { return _scope; }
		auto& functions() { return _functions; }

		friend std::ostream& operator<<(std::ostream& out, const PackageSymbolTable& package);
	};
}

#endif
