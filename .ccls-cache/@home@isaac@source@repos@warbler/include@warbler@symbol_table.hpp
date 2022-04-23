#ifndef WARBLER_SYMBOL_TABLE_HPP
#define WARBLER_SYMBOL_TABLE_HPP

#include <warbler/util/array.hpp>
#include <warbler/util/string.hpp>
#include <warbler/util/table.hpp>
#include <warbler/util/primitive.hpp>
#include <warbler/type.hpp>

namespace warbler
{
	struct SymbolContext
	{
		SymbolType type;
		u32 index;
		bool is_validated;

		SymbolContext(SymbolType type, u32 index, bool is_validated) :
		type(type),
		index(index),
		is_validated(is_validated)
		{}
	};

	class SymbolTable
	{
	private:

		const String& _package;
		Array<Table<SymbolContext>*> _scope;
	
	public:

		SymbolTable(Table<SymbolContext>& symbols, const String& package);

		void push_scope(Table<SymbolContext>& symbols);
		void pop_scope();	

		void add(const String& symbol, u32 index, SymbolType type);

		SymbolContext& resolve(const String& symbol);

		String get_symbol(const String& name);
	};
}

#endif
