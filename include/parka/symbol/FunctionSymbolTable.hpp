#ifndef PARKA_SYMBOLS_FUNCTION_SYMBOL_TABLE_HPP
#define PARKA_SYMBOLS_FUNCTION_SYMBOL_TABLE_HPP

#include "parka/symbol/BlockSymbolTable.hpp"
#include "parka/symbol/Identifier.hpp"
#include "parka/symbol/PackageSymbolTable.hpp"
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
		const SymbolTable *_parent;
		Table<String, SymbolTableEntry> _symbols;
		Array<BlockSymbolTable> _blocks;

		bool declare(const Identifier& identifier);

	public:

		FunctionSymbolTable(const EntitySyntaxId& functionId, const SymbolTable& parent) :
		_functionId(functionId),
		_parent(&parent)
		{}

		FunctionSymbolTable(FunctionSymbolTable&&);
		FunctionSymbolTable(const FunctionSymbolTable&) = delete;

		Optional<EntitySyntaxId> resolve(const Identifier& identifier) const;
		Optional<EntitySyntaxId> resolve(const QualifiedIdentifier& identifier) const;
		
		void addBlock(const ExpressionSyntaxId& blockId);
		void popBlock();
		
		SymbolTableType symbolTableType() const { return SymbolTableType::Function; }
		const SymbolTable *parent() const { return _parent; }

		friend class SymbolTableEntry;
	};
}

#endif

