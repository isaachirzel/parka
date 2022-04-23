#include <warbler/symbol_table.hpp>

namespace warbler
{
	SymbolTable::SymbolTable(Table<SymbolContext>& symbols, const String& package) :
	_package(package),
	_scope({ &symbols })
	{}

	void SymbolTable::push_scope(Table<SymbolContext>& scope)
	{
		_scope.push_back(&scope);
	}

	void SymbolTable::pop_scope()
	{
		_scope.pop_back();
	}

	void SymbolTable::add(const String& symbol, u32 index, SymbolType type)
	{
		auto& current_scope = *_scope.back();

		current_scope.emplace(symbol, SymbolContext(type, index, false));
	}
}
