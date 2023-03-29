#include "parka/symbol/symbol_table.hpp"
#include "parka/ast/primitive.hpp"
#include "parka/symbol/entity.hpp"
#include "parka/symbol/node_bank.hpp"
#include "parka/util/print.hpp"

#include <cstdlib>
#include <cassert>
#include <cstring>

bool SymbolTable::declareGlobal(Table<EntityId>& globalSymbols, EntityId id)
{
	// TODO: Add tokens for highlighting
	auto& entity = NodeBank::get(id);
	const auto& symbol = entity.symbol();

	print("Declaring symbol: $: `$`", id, symbol);

	auto result = globalSymbols.insert({ symbol,  id });

	if (!result.second)
	{
		// TODO: get previous entity
		auto previousId = result.first->second;

		print("Previous id: $ $", (int)id.type(), id.index());

		auto& previous = NodeBank::get(previousId);

		//TODO: invalidate entity previous.invalidate();

		printError( "`$` is already declared in this package.", symbol.c_str());
	}

	return result.second;
}

bool SymbolTable::declareLocal(EntityId id)
{
	auto& entity = NodeBank::get(id);
	auto blockIndex = _blocks.length() > 0
		? _blocks.back()
		: 0;
	auto i = _localSymbols.length();

	while (i > blockIndex)
	{
		i -= 1;

		auto previousId = _localSymbols[i];
		auto& previous = NodeBank::get(previousId);

		if (entity.symbol() == previous.symbol())
		{
			printError(entity.token(), "`$` is already declared in this block.", previous.symbol());
			printNote(previous.token(), "Previous declaration here.");

			return false;
		}
	}

	_localSymbols.push(id);

	return true;
}

Optional<EntityId> SymbolTable::resolve(const Token& token)
{
	// TODO: Optimize
	auto identifier = token.text();

	usize i = _localSymbols.length();

	while (i > 0)
	{
		i -= 1;

		auto id = _localSymbols[i];
		auto& entity = NodeBank::get(id);

		if (token == entity.symbol())
			return id;
	}

	i = _scope.count();

	while (i > 0)
	{
		i -= 1;

		auto symbol = _scope.createSymbolN(identifier, i);
		auto iter = _globalSymbols.find(symbol);

		if (iter != _globalSymbols.end())
			return EntityId(iter->second);
	}

	printError(token, "Unable to find `$`.", identifier.c_str());

	// TODO: Find missing imports, fuzzy match from symbols

	return {};
}

void SymbolTable::setScope(const String& symbol)
{
	_scope = Scope::from(symbol);
}

void SymbolTable::clearLocalSymbols()
{
	_blocks.clear();
	_localSymbols.clear();
}

void SymbolTable::pushBlock()
{
	auto offset = _localSymbols.length();

	_blocks.push(offset);
}

void SymbolTable::popBlock()
{
	_blocks.pop();
}
