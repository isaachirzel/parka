#ifndef WARBLER_SEMANTICS_SYMBOL_TABLE_HPP
#define WARBLER_SEMANTICS_SYMBOL_TABLE_HPP

#include <warbler/util/array.hpp>
#include <warbler/util/string.hpp>
#include <warbler/util/table.hpp>
#include <warbler/semantics/attributes.hpp>

namespace warbler::semantics
{
	class SymbolTable
	{
	private:

		Array<Table<Attributes>*> _scopes;
	
	public:

		SymbolTable() = default;

		void push_scope(Table<Attributes> *scope);
		void pop_scope();
		bool can_declare(const String& symbol);
		void declare(const String& symbol);

		Attributes *find(const String& symbol);
	};
}

#endif
