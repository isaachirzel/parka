#include "parka/symbol/BlockSymbolTable.hpp"
#include "parka/log/Log.hpp"
#include "parka/repository/EntityContext.hpp"

namespace parka
{
	BlockSymbolTable::BlockSymbolTable(FunctionSymbolTable& symbolTable) :
	_parent(symbolTable),
	_symbols(symbolTable._symbols),
	_baseIndex(symbolTable._symbols.length())
	{}

	BlockSymbolTable::~BlockSymbolTable()
	{
		_symbols.truncate(_baseIndex);
	}

	bool BlockSymbolTable::declare(const EntitySyntax& entity)
	{
		const auto& identifier = entity.identifier();

		for (const auto *entry : _symbols)
		{
			if (identifier == entry->identifier())
			{
				log::error("Declaration of `$` shadows a previously declared $.", identifier, entry->entityType());
				// TODO: Show previous declaration
				// TODO: Maybe insert anyway?
				return false;
			}
		}

		_symbols.push(&entity);

		return true;
	}

	const EntityContext *BlockSymbolTable::resolve(const Identifier& identifier)
	{
		return _parent.resolve(identifier);
	}

	const EntityContext *BlockSymbolTable::resolve(const QualifiedIdentifier& identifier)
	{
		return _parent.resolve(identifier);
	}
}