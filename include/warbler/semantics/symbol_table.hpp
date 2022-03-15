#ifndef WARBLER_SEMANTICS_SYMBOL_TABLE_HPP
#define WARBLER_SEMANTICS_SYMBOL_TABLE_HPP

#include <warbler/util/array.hpp>
#include <warbler/util/string.hpp>
#include <warbler/util/table.hpp>
#include <warbler/semantics/statement/variable.hpp>
#include <warbler/semantics/function/function.hpp>
#include <warbler/semantics/type/definition.hpp>
#include <warbler/semantics/symbol.hpp>

namespace warbler::semantics
{
	class SymbolTable
	{
	private:

		Array<const String*> _lexical_scope;
		Array<Table<Symbol>*> _scopes;
	
	public:

		SymbolTable(Table<Symbol>& module_scope);

		void push_scope(Table<Symbol>& scope);
		void pop_scope();

		void add_parameters(Array<Parameter>& parameter);
		void add_function(Function&& function);
		void add_variable(Variable&& declaration);
		void add_type(Definition&& type);

		Symbol *resolve(const String& symbol);
		String get_symbol(const String& name);
	};
}

#endif
