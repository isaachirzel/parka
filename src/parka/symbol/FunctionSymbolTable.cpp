#include "parka/symbol/FunctionSymbolTable.hpp"
#include "parka/enum/ExpressionType.hpp"
#include "parka/log/Indent.hpp"
#include "parka/log/Log.hpp"
#include "parka/symbol/SymbolTableEntry.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	FunctionSymbolTable::FunctionSymbolTable(const FunctionSyntax& syntax, const SymbolTable& parent) :
	_syntax(syntax),
	_parent(&parent),
	_symbols(16),
	_blockIndexes(8)
	{}

	bool FunctionSymbolTable::declare(const EntitySyntax& entity)
	{
		const auto& identifier = entity.identifier();
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
			
		_symbols.push(&entity);
		
		return true;
	}

	const EntitySyntax *FunctionSymbolTable::resolve(const Identifier&) const
	{
		log::notImplemented(here());
	}

	const EntitySyntax *FunctionSymbolTable::resolve(const QualifiedIdentifier&) const
	{
		log::notImplemented(here());
	}
	
	void FunctionSymbolTable::addBlock(const ExpressionSyntax& block)
	{
		log::notImplemented(here());
	}

	void FunctionSymbolTable::popBlock()
	{
		log::notImplemented(here());
	}
}
