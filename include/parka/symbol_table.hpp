#ifndef PARKA_SYMBOL_TABLE_HPP
#define PARKA_SYMBOL_TABLE_HPP

#include "parka/global_symbol_table.hpp"
#include "parka/local_symbol_table.hpp"
#include "parka/type.hpp"
#include "parka/util/optional.hpp"

class SymbolTable
{
	LocalEntityTable _localEntities;
	GlobalEntityTable& _globalEntities;

public:

	SymbolTable(GlobalEntityTable& globalEntities) :
	_globalEntities(globalEntities)
	{}
	SymbolTable(SymbolTable&&) = default;
	SymbolTable(const SymbolTable&) = delete;
	~SymbolTable() = default;

	Ref<EntityContext> resolve(const Token& token);
	Entity& getEntity(const EntityId& id) const;
	Optional<Type> getType(SymbolTable& symbols, Ref<Type> expected = {}) const;
	void pushBlock(Block& block);
	void popBlock();
};

#endif
