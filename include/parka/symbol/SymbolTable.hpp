#ifndef PARKA_SYMBOL_SYMBOL_TABLE_HPP
#define PARKA_SYMBOL_SYMBOL_TABLE_HPP

#include "parka/enum/SymbolTableType.hpp"
#include "parka/ast/IdentifierAst.hpp"
#include "parka/ast/QualifiedIdentifierAst.hpp"
#include "parka/ir/ConversionIr.hpp"
#include "parka/ir/LValueIr.hpp"
#include "parka/ir/OperatorIr.hpp"
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

		virtual Resolvable *findSymbol(const ast::Identifier& identifier) = 0;
		virtual ir::LValueIr *resolveSymbol(const ast::QualifiedIdentifier& identifier) = 0;
		virtual ir::OperatorIr *resolveBinaryOperator(OperatorType type, const ir::Type& left, const ir::Type *right) = 0;
		virtual ir::ConversionIr *resolveConversion(const ir::Type& from, const ir::Type& to) = 0;
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
