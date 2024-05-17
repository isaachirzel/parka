#ifndef PARKA_SYMBOL_PACKAGE_SYMBOL_TABLE_HPP
#define PARKA_SYMBOL_PACKAGE_SYMBOL_TABLE_HPP

#include "parka/ast/PackageAst.hpp"
#include "parka/enum/BinaryExpressionType.hpp"
#include "parka/ir/ConversionIr.hpp"
#include "parka/ir/LValueIr.hpp"
#include "parka/symbol/GlobalSymbolTable.hpp"
#include "parka/symbol/Resolvable.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/util/Table.hpp"

namespace parka
{
	class PackageSymbolTable: public SymbolTable
	{
		String _scope;
		Table<String, Resolvable*> _symbols;
		GlobalSymbolTable& _global;
		SymbolTable& _parent;

	public:

		PackageSymbolTable(const ast::PackageAst& ast, SymbolTable& parent);
		PackageSymbolTable(PackageSymbolTable&&) = default;
		PackageSymbolTable(const PackageSymbolTable&) = delete;

		Resolvable* findSymbol(const ast::Identifier& identifier);
		Resolvable* findInitialSymbol(const ast::Identifier& identifier);
		ir::LValueIr* resolveSymbol(const ast::QualifiedIdentifier& identifier);
		ir::BinaryOperatorIr* resolveBinaryOperator(BinaryExpressionType binaryExpressionType, const ir::TypeIr& left, const ir::TypeIr& right);
		Result<ir::ConversionIr*> resolveConversion(const ir::TypeIr& from, const ir::TypeIr& to);

		const String& scope() const { return _scope; }
		SymbolTable* parent() { return &_parent; }
		GlobalSymbolTable& global() { return _global; }

		friend std::ostream& operator<<(std::ostream& out, const PackageSymbolTable& package);
	};
}

#endif
