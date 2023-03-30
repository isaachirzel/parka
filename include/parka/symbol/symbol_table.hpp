#ifndef PARKA_SYMBOL_SYMBOL_TABLE_HPP
#define PARKA_SYMBOL_SYMBOL_TABLE_HPP

#include "parka/symbol/entity_id.hpp"
#include "parka/symbol/scope.hpp"
#include "parka/token.hpp"
#include "parka/util/optional.hpp"
#include "parka/util/table.hpp"

class SymbolTable
{
	Table<EntityId>& _globalSymbols;
	Array<EntityId> _localSymbols;
	Array<usize> _blocks;
	Scope _scope;

public:

	SymbolTable(Table<EntityId>& globalSymbols, const String& packageSymbol) :
	_globalSymbols(globalSymbols),
	_scope(Scope::from(packageSymbol))
	{}

	SymbolTable(SymbolTable&&) = default;
	SymbolTable(const SymbolTable&) = delete;
	~SymbolTable() = default;

	static bool declareGlobal(Table<EntityId>& globalSymbols, EntityId id);
	bool declareLocal(EntityId id);
	Optional<EntityId> resolve(const Token& token);
	Optional<EntityId> resolve(const String& identifier);
	void setScope(const String& symbol);
	void clearLocalSymbols();
	void pushBlock();
	void popBlock();
};

#endif
