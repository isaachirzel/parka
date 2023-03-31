#ifndef PARKA_SYMBOL_GLOBAL_SYMBOL_TABLE_HPP
#define PARKA_SYMBOL_GLOBAL_SYMBOL_TABLE_HPP

#include "parka/ast/operator/operator_key.hpp"
#include "parka/symbol/entity_id.hpp"
#include "parka/token.hpp"
#include "parka/util/optional.hpp"
#include "parka/util/string.hpp"
#include "parka/util/table.hpp"

class GlobalSymbolTable
{
	Table<String, EntityId> _globalSymbols;
	Table<OperatorKey, OperatorId> _operatorSymbols;

public:

	GlobalSymbolTable();

	bool declare(const EntityId& id);
	Optional<EntityId> resolve(const String& identifier);
};

#endif
