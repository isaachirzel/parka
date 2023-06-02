#ifndef PARKA_SYMBOLS_FUNCTION_SYMBOL_TABLE_HPP
#define PARKA_SYMBOLS_FUNCTION_SYMBOL_TABLE_HPP

#include "parka/symbol/BlockSymbolTable.hpp"
#include "parka/symbol/Identifier.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/syntax/FunctionSyntax.hpp"
#include "parka/util/Array.hpp"
#include "parka/util/String.hpp"

// TODO: Move constructor

namespace parka
{
	class SymbolTableEntry;

	class FunctionSymbolTable : public SymbolTable
	{
		EntitySyntaxId _functionId;
		const SymbolTable& _parent;
		Table<String, SymbolTableEntry> _symbols;
		Array<BlockSymbolTable> _blocks;

	public:

		// The symbol table will be created regardless of errors
		FunctionSymbolTable(const EntitySyntaxId& functionId, const SymbolTable& parent) :
		_functionId(functionId),
		_parent(parent)
		{}

		FunctionSymbolTable(FunctionSymbolTable&&) = default;
		FunctionSymbolTable(const FunctionSymbolTable&) = delete;

		bool declare(const Identifier& identifier);
		Optional<EntitySyntaxId> resolve(const Identifier& identifier) const;
		Optional<EntitySyntaxId> resolve(const QualifiedIdentifier& identifier) const;
		
		void addBlock(const ExpressionSyntaxId& blockId);
		void popBlock();
		
		SymbolTableType symbolTableType() const { return SymbolTableType::Function; }
	};
}

#endif

