#ifndef PARKA_SYMBOLS_BLOCK_SYMBOL_TABLE_HPP
#define PARKA_SYMBOLS_BLOCK_SYMBOL_TABLE_HPP

#include "parka/repository/ExpressionSyntaxId.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/syntax/BlockSyntax.hpp"
#include "parka/util/Array.hpp"
#include "parka/util/String.hpp"
#include "parka/util/Table.hpp"

// TODO: Move constructor

namespace parka
{
	class SymbolTableEntry;

	class BlockSymbolTable : public SymbolTable
	{
		friend class FunctionSymbolTable;
		friend class SymbolTableEntry;
		
		ExpressionSyntaxId _blockId;
		const SymbolTable *_parent;
		Table<String, SymbolTableEntry> _symbols;
		Array<BlockSymbolTable> _blocks;

	private:

		bool declare(const Identifier& identifier);

	public:

		BlockSymbolTable(const ExpressionSyntaxId& blockId, const SymbolTable& parent) :
		_blockId(blockId),
		_parent(&parent)
		{}

		BlockSymbolTable(BlockSymbolTable&&) = default;
		BlockSymbolTable(const BlockSymbolTable&) = delete;

		Optional<EntitySyntaxId> resolve(const Identifier& identifier) const;
		Optional<EntitySyntaxId> resolve(const QualifiedIdentifier& identifier) const;

		SymbolTableType symbolTableType() const { return SymbolTableType::Block; }
		const SymbolTable *parent() const { return _parent; }
	};
}

#endif
