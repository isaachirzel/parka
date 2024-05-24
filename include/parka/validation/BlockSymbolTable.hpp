#ifndef PARKA_VALIDATION_BLOCK_SYMBOL_TABLE_HPP
#define PARKA_VALIDATION_BLOCK_SYMBOL_TABLE_HPP

#include "parka/validation/FunctionSymbolTable.hpp"
#include "parka/validation/LocalSymbolTable.hpp"
#include "parka/util/FlatMap.hpp"

namespace parka::validation
{
	class BlockSymbolTable: public LocalSymbolTable
	{
		GlobalSymbolTable& _global;
		FunctionSymbolTable& _function;
		SymbolTable& _parent;
		String _scope;
		FlatMap<String, Resolvable*> _symbols;
		bool _isInLoop;

		BlockSymbolTable(FunctionSymbolTable& function, SymbolTable& parent);

	public:

		BlockSymbolTable(LocalSymbolTable& parent);
		BlockSymbolTable(BlockSymbolTable&&) = default;
		BlockSymbolTable(const BlockSymbolTable&) = delete;

		FunctionEntry& declare(const ast::FunctionAst& ast);
		VariableEntry& declare(const ast::VariableAst& ast);
		ParameterEntry& declare(const ast::ParameterAst& ast);
		Resolvable* findSymbol(const ast::IdentifierAst& identifier);
		ir::LValueIr* resolveSymbol(const ast::QualifiedIdentifierAst& identifier);
		ir::BinaryOperatorIr* resolveBinaryOperator(BinaryExpressionType binaryExpressionType, const ir::TypeIr& left, const ir::TypeIr& right);
		ir::AssignmentOperatorIr* resolveAssignmentOperator(const ir::TypeIr& left, const ir::TypeIr& right, AssignmentType assignmentType);
		Result<ir::ConversionIr*> resolveConversion(const ir::TypeIr& to, const ir::TypeIr& from);
		const String& scope() const { return _scope; }
		SymbolTable* parent() { return &_parent; }
		const ir::TypeIr& returnType() const { return _function.returnType(); }
		void setInLoop() { _isInLoop = true; }
		bool isInLoop() const { return _isInLoop; }
		FunctionSymbolTable& functionSymbolTable() { return _function; }
		GlobalSymbolTable& globalSymbolTable() { return _global; }
	};
}

#endif
