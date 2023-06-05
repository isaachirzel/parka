#include "parka/symbol/FunctionSymbolTable.hpp"
#include "parka/enum/ExpressionType.hpp"
#include "parka/log/Indent.hpp"
#include "parka/log/Log.hpp"
#include "parka/repository/EntitySyntaxId.hpp"
#include "parka/symbol/SymbolTableEntry.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	FunctionSymbolTable::FunctionSymbolTable(const EntitySyntaxId& functionId, const SymbolTable& parent) :
	_functionId(functionId),
	_parent(&parent),
	_symbols(16),
	_blockIndexes(8)
	{}

	void FunctionSymbolTable::declare(const EntitySyntaxId& entityId)
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
				log::error("Value `$` has previously been delcared in this scope.", identifier);
				// TODO: Maybe insert it anyway so that references to it will show the correct error
				return;
			}
		}
			
		_symbols.push(entityId);
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
