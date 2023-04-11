#ifndef PARKA_SYMBOLS_BLOCK_SYMBOL_TABLE_HPP
#define PARKA_SYMBOLS_BLOCK_SYMBOL_TABLE_HPP

#include "parka/symbol/Identifier.hpp"
#include "parka/symbol/QualifiedIdentifier.hpp"
#include "parka/repository/EntitySyntaxId.hpp"
#include "parka/repository/ExpressionSyntaxId.hpp"
#include "parka/util/Array.hpp"
#include "parka/util/String.hpp"
#include "parka/util/Table.hpp"

namespace parka
{
	class FunctionSymbolTable;

	class BlockSymbolTable
	{
		ExpressionSyntaxId _blockId;
		const BlockSymbolTable *_parentBlock;
		const FunctionSymbolTable& _parentFunction;
		Table<String, EntitySyntaxId> _symbols;
		Array<BlockSymbolTable> _blocks;

	public:

		BlockSymbolTable(const ExpressionSyntaxId& blockId, const FunctionSymbolTable& parentFunction) :
		_blockId(blockId),
		_parentBlock(nullptr),
		_parentFunction(parentFunction)
		{}
		BlockSymbolTable(const ExpressionSyntaxId& blockId, const BlockSymbolTable& parentBlock) :
		_blockId(blockId),
		_parentBlock(&parentBlock),
		_parentFunction(parentBlock._parentFunction)
		{}


		bool declare(const Identifier& identifier);
		Optional<EntitySyntaxId> resolve(const Identifier& identifier) const;
		Optional<EntitySyntaxId> resolve(const QualifiedIdentifier& identifier) const;

		friend class FunctionSymbolTable;
	};
}

#endif
