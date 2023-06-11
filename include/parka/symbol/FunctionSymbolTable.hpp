#ifndef PARKA_SYMBOLS_FUNCTION_SYMBOL_TABLE_HPP
#define PARKA_SYMBOLS_FUNCTION_SYMBOL_TABLE_HPP

#include "parka/symbol/SymbolTable.hpp"
#include "parka/syntax/EntitySyntax.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/util/Array.hpp"

namespace parka
{
	class FunctionSyntax;
	
	class FunctionSymbolTable : public SymbolTable
	{
		SymbolTable *_parent;
		const FunctionSyntax& _syntax;
		Array<const EntitySyntax*> _symbols;		

	public:

		FunctionSymbolTable(const FunctionSyntax& syntax, SymbolTable& parent);
		FunctionSymbolTable(FunctionSymbolTable&&) = default;
		FunctionSymbolTable(const FunctionSymbolTable&) = delete;

		bool declare(const EntitySyntax& entity);

		const EntityContext *resolve(const Identifier& identifier);
		const EntityContext *resolve(const QualifiedIdentifier& identifier);
		
		void addBlock(const ExpressionSyntax& blockId);
		void popBlock();
		
		SymbolTableType symbolTableType() const { return SymbolTableType::Function; }
		SymbolTable *parent() { return _parent; }

		const auto& syntax() const { return (const FunctionSyntax&)_syntax; }

		friend class BlockSymbolTable;
	};
}

#endif

