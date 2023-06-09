#include "parka/symbol/FunctionSymbolTable.hpp"
#include "parka/enum/ExpressionType.hpp"
#include "parka/log/Indent.hpp"
#include "parka/log/Log.hpp"
#include "parka/symbol/SymbolTableEntry.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	FunctionSymbolTable::FunctionSymbolTable(const FunctionSyntax& syntax, SymbolTable& parent) :
	_parent(&parent),
	_syntax(syntax),
	_symbols(16)
	{}

	bool FunctionSymbolTable::declare(const EntitySyntax& entity)
	{
		const auto& identifier = entity.identifier();

		for (const auto *symbol : _symbols)
		{
			if (identifier == symbol->identifier())
			{
				log::error("A parameter with the name `$` has already been declared in this prototype.", identifier);
				// TODO: maybe just insert it anyways?
				return false;
			}
		}

		_symbols.push(&entity);
		
		return true;
	}

	const EntityContext *FunctionSymbolTable::resolve(const Identifier&)
	{
		log::notImplemented(here());
	}

	const EntityContext *FunctionSymbolTable::resolve(const QualifiedIdentifier&)
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
