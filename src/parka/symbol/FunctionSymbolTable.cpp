#include "parka/symbol/FunctionSymbolTable.hpp"
#include "parka/symbol/SymbolTableEntry.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	FunctionSymbolTable::FunctionSymbolTable(FunctionSymbolTable&& other) :
	_functionId(std::move(other._functionId)),
	_parent(other._parent),
	_symbols(std::move(other._symbols)),
	_blocks(std::move(other._blocks))
	{
		for (auto& tuple : _symbols)
		{
			auto& entry = tuple.value();

			entry.setParent(*this);
		}

		for (auto& _block : _blocks)
			_block._parent = this;
	}

	bool FunctionSymbolTable::declare(const Identifier&)
	{
		exitNotImplemented(here());
	}

	Optional<EntitySyntaxId> FunctionSymbolTable::resolve(const Identifier&) const
	{
		exitNotImplemented(here());
	}

	Optional<EntitySyntaxId> FunctionSymbolTable::resolve(const QualifiedIdentifier&) const
	{
		exitNotImplemented(here());
	}
	
	void FunctionSymbolTable::addBlock(const ExpressionSyntaxId&)
	{
		exitNotImplemented(here());
	}

	void FunctionSymbolTable::popBlock()
	{
		exitNotImplemented(here());
	}
}
