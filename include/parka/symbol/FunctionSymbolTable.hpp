#ifndef PARKA_SYMBOL_FUNCTION_SYMBOL_TABLE_HPP
#define PARKA_SYMBOL_FUNCTION_SYMBOL_TABLE_HPP

#include "parka/ast/IdentifierAst.hpp"
#include "parka/ir/StatementIr.hpp"
#include "parka/ir/TypeIr.hpp"
#include "parka/symbol/Resolvable.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/symbol/VariableEntry.hpp"
#include "parka/symbol/ParameterEntry.hpp"

namespace parka
{
	struct Resolvable;
	class GlobalSymbolTable;

	class FunctionSymbolTable: public SymbolTable
	{
		GlobalSymbolTable& _global;
		SymbolTable& _parent;
		String _scope;
		Array<Resolvable*> _symbols;
		Array<VariableEntry> _variables;
		Array<ParameterEntry> _parameters;
		ir::TypeIr _returnType;
		Array<ir::StatementIr*> _parentStatements;

	private:

		bool declare(const ast::Identifier& identifier, Resolvable *resolvable);

	public:

		FunctionSymbolTable(SymbolTable &parent);
		FunctionSymbolTable(FunctionSymbolTable&&) = default;
		FunctionSymbolTable(const FunctionSymbolTable&) = delete;

		ParameterEntry* declare(ParameterEntry&& entry);
		VariableEntry* declare(VariableEntry&& entry);
		Resolvable* findSymbol(const ast::Identifier& identifier);
		ir::LValueIr* resolveSymbol(const ast::QualifiedIdentifier& identifier);
		ir::BinaryOperatorIr* resolveBinaryOperator(BinaryExpressionType binaryExpressionType, const ir::TypeIr& left, const ir::TypeIr& right);
		Result<ir::ConversionIr*> resolveConversion(const ir::TypeIr& to, const ir::TypeIr& from);
		

		void setReturnType(const ir::TypeIr& type) { _returnType = type; }
		const auto& returnType() const { return _returnType; }
		const String& scope() const { return _scope; }
		SymbolTable* parent() { return &_parent; }
		GlobalSymbolTable& global() { return _global; }

		friend std::ostream& operator<<(std::ostream& out, const FunctionSymbolTable& syntax);
	};
}

#endif
