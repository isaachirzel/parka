#ifndef PARKA_SYMBOL_SYMBOL_TABLE_HPP
#define PARKA_SYMBOL_SYMBOL_TABLE_HPP

#include "parka/ast/FunctionAst.hpp"
#include "parka/ast/ParameterAst.hpp"
#include "parka/ast/VariableAst.hpp"
#include "parka/enum/BinaryExpressionType.hpp"
#include "parka/enum/SymbolTableType.hpp"
#include "parka/ast/IdentifierAst.hpp"
#include "parka/ast/QualifiedIdentifierAst.hpp"
#include "parka/ir/ConversionIr.hpp"
#include "parka/ir/LValueIr.hpp"
#include "parka/ir/BinaryOperatorIr.hpp"

namespace parka
{
	class GlobalSymbolTable;
	struct Resolvable;
	class FunctionEntry;
	class VariableEntry;
	class ParameterEntry;


	struct SymbolTable
	{
		const SymbolTableType symbolTableType;

		SymbolTable(SymbolTableType symbolTableType):
			symbolTableType(symbolTableType)
		{}
		virtual ~SymbolTable() {}

		virtual FunctionEntry& declare (const ast::FunctionAst& ast) = 0;
		virtual VariableEntry& declare (const ast::VariableAst& ast) = 0;
		virtual ParameterEntry& declare (const ast::ParameterAst& ast) = 0;
		virtual Resolvable* findSymbol(const ast::Identifier& identifier) = 0;
		virtual ir::LValueIr* resolveSymbol(const ast::QualifiedIdentifier& identifier) = 0;
		virtual ir::BinaryOperatorIr* resolveBinaryOperator(BinaryExpressionType binaryExpressionType, const ir::TypeIr& left, const ir::TypeIr& right) = 0;
		virtual Result<ir::ConversionIr*> resolveConversion(const ir::TypeIr& to, const ir::TypeIr& from) = 0;
		virtual const String& scope() const = 0;
		virtual SymbolTable* parent() = 0;
		virtual GlobalSymbolTable& global() = 0;

		String createSymbol(const String& name) const
		{
			const auto& scope = this->scope();

			if (scope.empty())
				return name;

			auto length = scope.length() + 2 + name.length();
			auto symbol = String();

			symbol.reserve(length);
			symbol += scope;
			symbol += "::";
			symbol += name;

			return symbol;
		}
	};
}

#endif
