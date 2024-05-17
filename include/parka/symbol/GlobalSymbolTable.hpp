#ifndef PARKA_SYMBOL_GLOBAL_SYMBOL_TABLE_HPP
#define PARKA_SYMBOL_GLOBAL_SYMBOL_TABLE_HPP

#include "parka/ast/FunctionAst.hpp"
#include "parka/ast/PackageAst.hpp"
#include "parka/symbol/FunctionEntry.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/util/Table.hpp"

namespace parka
{
	class GlobalSymbolTable: public SymbolTable
	{
		String _scope;
		Table<String, Resolvable*> _symbols;
		Array<ir::BinaryOperatorIr*> _operators;
		Array<ir::ConversionIr*> _conversions;
		Array<FunctionEntry> _functions;

	public:

		GlobalSymbolTable(const ast::PackageAst& globalPackage);
		GlobalSymbolTable(GlobalSymbolTable&&) = default;
		GlobalSymbolTable(const GlobalSymbolTable&) = delete;

		FunctionEntry& addFunction(FunctionEntry&& entry);

		FunctionEntry* declare(ast::FunctionAst& entry);

		Resolvable* findSymbol(const ast::Identifier& identifier);
		ir::LValueIr* resolveSymbol(const ast::QualifiedIdentifier& identifier);
		ir::BinaryOperatorIr* resolveBinaryOperator(BinaryExpressionType binaryExpressionType, const ir::TypeIr& left, const ir::TypeIr& right);
		Result<ir::ConversionIr*> resolveConversion(const ir::TypeIr& to, const ir::TypeIr& from);
		const String& scope() const;
		SymbolTable* parent() { return nullptr; }
		GlobalSymbolTable& global() { return *this; }

		auto& functions() { return _functions; }
	};
}

#endif
