#ifndef WARBLER_SEMANTICS_SYMBOL_TABLE_HPP
#define WARBLER_SEMANTICS_SYMBOL_TABLE_HPP

#include <warbler/util/array.hpp>
#include <warbler/util/string.hpp>
#include <warbler/util/table.hpp>

namespace warbler
{
	// Forward declarations
	class FunctionContext;
	class ParameterContext;
	class VariableContext;
	class TypeDefinitionContext;
	class SymbolContext;

	class SymbolTable
	{
	private:

		Array<const String*> _package;
		Array<Table<SymbolContext>*> _scope;
	
	public:

		SymbolTable(Table<SymbolContext>& module_scope);

		void push_scope(Table<SymbolContext>& scope);
		void pop_scope();

		void add_parameters(Array<ParameterContext>& parameter);
		void add_function(FunctionContext& function);
		void add_variable(VariableContext& declaration);
		void add_type(TypeDefinitionContext& type);

		SymbolContext *resolve(const String& symbol);

		String get_symbol(const String& name);
	};
}

#endif
