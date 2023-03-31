#include "parka/symbol/local_symbol_table.hpp"
#include "parka/symbol/entity_id.hpp"
#include "parka/symbol/node_bank.hpp"
#include "parka/util/print.hpp"

bool LocalSymbolTable::declare(const EntityId& id)
{
	auto& entity = NodeBank::get(id);
	print("Declaring $ $", id.type(), entity.symbol());
	auto blockIndex = _blocks.length() > 0
		? _blocks.back()
		: 0;

	for (auto i = blockIndex; i < _localSymbols.length(); ++i)
	{
		auto previousId = _localSymbols[i];
		auto& previous = NodeBank::get(previousId);

		if (entity.symbol() == previous.symbol())
		{
			printError(entity.token(), "`$` is already declared in this block.", previous.symbol());
			printNote(previous.token(), "Previous declaration here.");

			return false;
		}
	}

	_localSymbols.push(EntityId(id));

	return true;
}

Optional<EntityId> LocalSymbolTable::resolve(const Token& token)
{
	auto identifier = token.text();
	auto i = _localSymbols.length();

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
		auto result = _globalSymbols.resolve(symbol);

		if (result)
			return result;
	}

	return {};
}

void LocalSymbolTable::pushBlock()
{
	auto offset = _localSymbols.length();

	_blocks.push(offset);
}

void LocalSymbolTable::popBlock()
{
	_blocks.pop();
}

void LocalSymbolTable::clear()
{
	_blocks.clear();
	_localSymbols.clear();
}
