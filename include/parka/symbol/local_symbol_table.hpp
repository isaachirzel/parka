#ifndef PARKA_SYMBOL_LOCAL_SYMBOL_TABLE_HPP
#define PARKA_SYMBOL_LOCAL_SYMBOL_TABLE_HPP

#include "parka/symbol/entity_id.hpp"
#include "parka/symbol/global_symbol_table.hpp"
#include "parka/symbol/scope.hpp"
#include "parka/token.hpp"
#include "parka/util/optional.hpp"

class LocalSymbolTable
{
	GlobalSymbolTable& _globalSymbols;
	Array<EntityId> _localSymbols;
	Array<usize> _blocks;
	Scope _scope;

public:

	LocalSymbolTable(GlobalSymbolTable& globalSymbols, const String& packageSymbol) :
	_globalSymbols(globalSymbols),
	_localSymbols(64),
	_blocks(8),
	_scope(Scope::from(packageSymbol))
	{}

	LocalSymbolTable(LocalSymbolTable&&) = default;
	LocalSymbolTable(const LocalSymbolTable&) = delete;
	~LocalSymbolTable() = default;
	
	bool declare(const EntityId& id);
	Optional<EntityId> resolve(const Token& token);
	Optional<EntityId> resolve(const String& identifier);
	void clear();
	void pushBlock();
	void popBlock();
};

#endif
