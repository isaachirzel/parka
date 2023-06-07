#include "parka/symbol/FunctionSymbolTable.hpp"
#include "parka/enum/ExpressionType.hpp"
#include "parka/log/Indent.hpp"
#include "parka/log/Log.hpp"
#include "parka/repository/EntitySyntaxId.hpp"
#include "parka/symbol/SymbolTableEntry.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	FunctionSymbolTable::FunctionSymbolTable(const EntitySyntaxId& syntaxId, const SymbolTable& parent) :
	_syntaxId(syntaxId),
	_parent(&parent),
	_symbols(16),
	_blockIndexes(8)
	{}

	bool FunctionSymbolTable::declare(const EntitySyntaxId& entityId)
	{
		const auto& identifier = entityId->identifier();
		auto blockIndex = _blockIndexes.length() > 0
			? _blockIndexes.back()
			: 0;
		
		for (usize i = _symbols.length(); i-- > blockIndex;)
		{
			const auto& prevId = _symbols[i];

			if (identifier == prevId->identifier())
			{
				log::error("`$` has previously been delcared in this block.", identifier);
				// TODO: Maybe insert it anyway so that references to it will show the correct error
				return false;
			}
		}
			
		_symbols.push(entityId);
		
		return true;
	}

	Optional<EntitySyntaxId> FunctionSymbolTable::resolve(const Identifier&) const
	{
		log::notImplemented(here());
	}

	Optional<EntitySyntaxId> FunctionSymbolTable::resolve(const QualifiedIdentifier&) const
	{
		log::notImplemented(here());
	}
	
	void FunctionSymbolTable::addBlock(const ExpressionSyntaxId&)
	{
		log::notImplemented(here());
	}

	void FunctionSymbolTable::popBlock()
	{
		log::notImplemented(here());
	}
}
