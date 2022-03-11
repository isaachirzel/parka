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

		String _module_name;
		Array<Definition> _type_definitions;
		Array<Table<Symbol>*> _scopes;
	
	public:

		SymbolTable(const String& module_name, Table<Symbol>& module_scope);

		void push_scope(Table<Symbol>& scope);
		void pop_scope();

		bool has_symbol(const String& symbol);
		void add_parameter(const String& name, Parameter& parameter);
		void add_function(const String& name, Function& function);
		void add_variable(const String& name, Variable& declaration);
		void add_type(const String& name, Definition& type);

		Symbol *resolve(const String& symbol);
	};
}

#endif
