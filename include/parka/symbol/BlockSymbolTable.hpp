#ifndef PARKA_SYMBOLS_BLOCK_SYMBOL_TABLE_HPP
#define PARKA_SYMBOLS_BLOCK_SYMBOL_TABLE_HPP

#include "parka/symbol/Identifier.hpp"
#include "parka/symbol/QualifiedIdentifier.hpp"
#include "parka/data/EntityId.hpp"
#include "parka/data/ExpressionId.hpp"
#include "parka/util/Array.hpp"
#include "parka/util/String.hpp"
#include "parka/util/Table.hpp"

namespace parka
{
	class FunctionSymbolTable;

	class BlockSymbolTable
	{
		ExpressionId _blockId;
		const BlockSymbolTable *_parentBlock;
		const FunctionSymbolTable& _parentFunction;
		Table<String, EntityId> _symbols;
		Array<BlockSymbolTable> _blocks;

	public:

		BlockSymbolTable(const ExpressionId& blockId, const FunctionSymbolTable& parentFunction) :
		_blockId(blockId),
		_parentBlock(nullptr),
		_parentFunction(parentFunction)
		{}
		BlockSymbolTable(const ExpressionId& blockId, const BlockSymbolTable& parentBlock) :
		_blockId(blockId),
		_parentBlock(&parentBlock),
		_parentFunction(parentBlock._parentFunction)
		{}


		bool declare(const Identifier& identifier);
		Optional<EntityId> resolve(const Identifier& identifier) const;
		Optional<EntityId> resolve(const QualifiedIdentifier& identifier) const;

		friend class FunctionSymbolTable;
	};
}

#endif
