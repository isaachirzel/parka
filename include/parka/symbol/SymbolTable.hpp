#ifndef PARKA_SYMBOL_SYMBOL_TABLE_HPP
#define PARKA_SYMBOL_SYMBOL_TABLE_HPP

#include "parka/enum/BinaryExpressionType.hpp"
#include "parka/enum/SymbolTableType.hpp"
#include "parka/ast/IdentifierAst.hpp"
#include "parka/ast/QualifiedIdentifierAst.hpp"
#include "parka/ir/ConversionIr.hpp"
#include "parka/ir/LValueIr.hpp"
#include "parka/ir/BinaryOperatorIr.hpp"
#include "parka/symbol/Resolvable.hpp"

namespace parka
{
	struct SymbolTable
	{
		const SymbolTableType symbolTableType;

		SymbolTable(SymbolTableType symbolTableType):
			symbolTableType(symbolTableType)
		{}
		virtual ~SymbolTable() {}

		virtual Resolvable* findSymbol(const ast::Identifier& identifier) = 0;
		virtual ir::LValueIr* resolveSymbol(const ast::QualifiedIdentifier& identifier) = 0;
		virtual ir::BinaryOperatorIr* resolveBinaryOperator(BinaryExpressionType type, const ir::Type& left, const ir::Type& right) = 0;
		virtual Result<ir::ConversionIr*> resolveConversion(const ir::Type& to, const ir::Type& from) = 0;
		virtual const String& scope() const = 0;

		String createSymbol(const String& name)
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
