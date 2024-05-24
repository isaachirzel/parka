#ifndef PARKA_VALIDATION_FUNCTION_SYMBOL_TABLE_HPP
#define PARKA_VALIDATION_FUNCTION_SYMBOL_TABLE_HPP

#include "parka/ast/IdentifierAst.hpp"
#include "parka/ast/ParameterAst.hpp"
#include "parka/ast/VariableAst.hpp"
#include "parka/ir/TypeIr.hpp"
#include "parka/validation/LocalSymbolTable.hpp"
#include "parka/validation/Resolvable.hpp"
#include "parka/validation/VariableEntry.hpp"
#include "parka/validation/ParameterEntry.hpp"
#include "parka/util/FlatMap.hpp"

namespace parka::validation
{
	struct Resolvable;
	class GlobalSymbolTable;

	class FunctionSymbolTable: public LocalSymbolTable
	{
		GlobalSymbolTable& _global;
		SymbolTable& _parent;
		String _scope;
		FlatMap<String, Resolvable*> _symbols;
		Array<VariableEntry> _variables;
		Array<ParameterEntry> _parameters;
		ir::TypeIr _returnType;
		bool _isExplicitReturnType;

	public:

		FunctionSymbolTable(SymbolTable &parent);
		FunctionSymbolTable(FunctionSymbolTable&&) = default;
		FunctionSymbolTable(const FunctionSymbolTable&) = delete;

		VariableEntry& addVariable(VariableEntry&& entry);
		ParameterEntry& addParameter(ParameterEntry&& entry);

		FunctionEntry& declare(const ast::FunctionAst& ast);
		VariableEntry& declare(const ast::VariableAst& ast);
		ParameterEntry& declare(const ast::ParameterAst& ast);
		Resolvable* findSymbol(const ast::IdentifierAst& identifier);
		ir::LValueIr* resolveSymbol(const ast::QualifiedIdentifierAst& identifier);
		ir::BinaryOperatorIr* resolveBinaryOperator(BinaryExpressionType binaryExpressionType, const ir::TypeIr& left, const ir::TypeIr& right);
		ir::AssignmentOperatorIr* resolveAssignmentOperator(const ir::TypeIr& left, const ir::TypeIr& right, AssignmentType assignmentType);
		Result<ir::ConversionIr*> resolveConversion(const ir::TypeIr& to, const ir::TypeIr& from);
		
		void setReturnType(const ir::TypeIr& type) { _returnType = type; }
		const ir::TypeIr& returnType() const { return _returnType; }
		void setIsExplicitReturnType(bool value) { _isExplicitReturnType = value; }
		const auto& isExplicitReturnType() const { return _isExplicitReturnType; }
		const String& scope() const { return _scope; }
		SymbolTable* parent() { return &_parent; }
		GlobalSymbolTable& globalSymbolTable() { return _global; }
		FunctionSymbolTable& functionSymbolTable() { return *this; }
		bool isInLoop() const { return false; }
	};
}

#endif
