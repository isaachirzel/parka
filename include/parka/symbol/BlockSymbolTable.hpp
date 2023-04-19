#ifndef PARKA_SYMBOLS_BLOCK_SYMBOL_TABLE_HPP
#define PARKA_SYMBOLS_BLOCK_SYMBOL_TABLE_HPP

#include "parka/repository/ExpressionSyntaxId.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/syntax/BlockSyntax.hpp"
#include "parka/util/Array.hpp"
#include "parka/util/String.hpp"
#include "parka/util/Table.hpp"

namespace parka
{
	class BlockSymbolTable : public SymbolTable
	{
		ExpressionSyntaxId _blockId;
		const SymbolTable& _parent;
		Table<String, EntitySyntaxId> _symbols;
		Array<BlockSymbolTable> _blocks;

		BlockSymbolTable(const ExpressionSyntaxId& blockId, const SymbolTable& parent) :
		_blockId(blockId),
		_parent(parent)
		{}

	public:

		BlockSymbolTable(BlockSymbolTable&&) = default;
		BlockSymbolTable(const BlockSymbolTable&) = delete;

		static Optional<BlockSymbolTable> from(const BlockSyntax& block);

		bool declare(const Identifier& identifier);
		Optional<EntitySyntaxId> resolve(const Identifier& identifier) const;
		Optional<EntitySyntaxId> resolve(const QualifiedIdentifier& identifier) const;

		friend class FunctionSymbolTable;
	};
}

#endif
