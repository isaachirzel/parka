#ifndef WARBLER_SEMANTICS_SYMBOL_TABLE_HPP
#define WARBLER_SEMANTICS_SYMBOL_TABLE_HPP

#include <warbler/util/array.hpp>
#include <warbler/util/string.hpp>
#include <warbler/util/table.hpp>
#include <warbler/util/primitive>

namespace warbler
{
	enum class SymbolType
	{
		Function,
		Parameter,
		Variable,
		TypeDefinition
	}

	struct SymbolContext
	{
		SymbolType type;
		u32 index;
		bool is_validated;
	};

	struct Scope
	{
		const String& package;
		Table<SymbolContext>& symbols;
	};


	class SymbolTable
	{
	private:

		Array<Scope> _scope;
	
	public:

		SymbolTable(Table<SymbolContext>& module_scope, const String& package);

		void push_scope(Table<SymbolContext>& symbols, const String& package);
		void pop_scope();		

		void add(const String& symbol, SymbolType type);

		SymbolContext& resolve(const String& symbol);

		String get_symbol(const String& name);
	};
}

#endif
