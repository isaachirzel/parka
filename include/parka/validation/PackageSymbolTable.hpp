#ifndef PARKA_VALIDATION_PACKAGE_SYMBOL_TABLE_HPP
#define PARKA_VALIDATION_PACKAGE_SYMBOL_TABLE_HPP

#include "parka/ast/PackageAst.hpp"
#include "parka/enum/BinaryExpressionType.hpp"
#include "parka/ir/ConversionIr.hpp"
#include "parka/ir/LValueIr.hpp"
#include "parka/validation/GlobalSymbolTable.hpp"
#include "parka/validation/Resolvable.hpp"
#include "parka/validation/SymbolTable.hpp"

namespace parka::validation
{
	class PackageSymbolTable: public SymbolTable
	{
		String _scope;
		FlatMap<String, Resolvable*> _symbols;
		GlobalSymbolTable& _global;
		SymbolTable& _parent;

	public:

		PackageSymbolTable(const ast::PackageAst& ast, SymbolTable& parent);
		PackageSymbolTable(PackageSymbolTable&&) = default;
		PackageSymbolTable(const PackageSymbolTable&) = delete;

		FunctionEntry& declare(const ast::FunctionAst& ast);
		VariableEntry& declare(const ast::VariableAst& ast);
		ParameterEntry& declare(const ast::ParameterAst& ast);
		Resolvable* findSymbol(const ast::IdentifierAst& identifier);
		Resolvable* findInitialSymbol(const ast::IdentifierAst& identifier);
		ir::LValueIr* resolveSymbol(const ast::QualifiedIdentifierAst& identifier);
		ir::BinaryOperatorIr* resolveBinaryOperator(BinaryExpressionType binaryExpressionType, const ir::TypeIr& left, const ir::TypeIr& right);
		ir::AssignmentOperatorIr* resolveAssignmentOperator(const ir::TypeIr& left, const ir::TypeIr& right, AssignmentType assignmentType);
		Result<ir::ConversionIr*> resolveConversion(const ir::TypeIr& from, const ir::TypeIr& to);

		const String& scope() const { return _scope; }
		SymbolTable* parent() { return &_parent; }
		GlobalSymbolTable& globalSymbolTable() { return _global; }
	};
}

#endif
