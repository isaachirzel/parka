#include <warbler/symbol_table.hpp>

namespace warbler
{
	SymbolTable::SymbolTable(Table<SymbolContext>& module_scope) :
	_scope({ &module_scope })
	{}

	void SymbolTable::push_scope(Table<SymbolContext>& scope)
	{
		_scope.push_back(&scope);
	}

	void SymbolTable::pop_scope()
	{
		_scope.pop_back();
	}

	void SymbolTable::add(const String& symbol, SymbolType type)
	{
		auto current_scope = _scope.back();

		current_scope.symbols.insert(SymbolContext { type, 0, false });
	}
}
