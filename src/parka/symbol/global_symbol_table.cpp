#include "parka/symbol/global_symbol_table.hpp"
#include "parka/symbol/node_bank.hpp"
#include "parka/util/print.hpp"

GlobalSymbolTable::GlobalSymbolTable() :
_globalSymbols(NodeBank::getGlobalCount())
{
	NodeBank::declarePrimitives(_globalSymbols);
}

bool GlobalSymbolTable::declare(const EntityId& id)
{
	// TODO: Add tokens for highlighting
	auto& entity = NodeBank::get(id);
	const auto& symbol = entity.symbol();

	print("Declaring symbol: $: `$`", id, symbol);

	auto result = _globalSymbols.insert({ symbol,  id });

	if (!result.second)
	{
		// TODO: get previous entity
		// auto previousId = result.first->second;
		// auto& previous = NodeBank::get(previousId);
		//TODO: invalidate entity previous.invalidate();

		printError("`$` is already declared in this package.", symbol);
	}

	return result.second;
}

Optional<EntityId> GlobalSymbolTable::resolve(const String& symbol)
{
	auto iter = _globalSymbols.find(symbol);

	if (iter == _globalSymbols.end())
		return {};

	return iter->second;
}
