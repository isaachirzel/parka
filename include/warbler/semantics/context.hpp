#ifndef WARBLER_SEMANTICS_SYMBOL_TABLE_HPP
#define WARBLER_SEMANTICS_SYMBOL_TABLE_HPP

#include <warbler/util/array.hpp>
#include <warbler/util/string.hpp>
#include <warbler/util/table.hpp>
#include <warbler/semantics/attributes.hpp>

namespace warbler::syntax
{
	class Parameter;
	class Function;
	class Declaration;
	class TypeDefinition;
}

namespace warbler::semantics
{
	class Context
	{
	private:

		Array<Definition> _type_definitions;
		Array<Scope*> _scopes;
	
	public:

		Context(const String& module_name, Table<SymbolContext> *module_scope);

		void push_scope(Scope *scope);
		void pop_scope();

		bool has_symbol(const String& symbol);
		void add_parameter(const String& name, syntax::Parameter *parameter);
		void add_function(const String& name, syntax::Function *function);
		void add_variable(const String& name, syntax::Declaration *declaration);
		void add_type(const String& name, syntax::TypeDefinition *type);

		SymbolContext *find(const String& symbol);
	};
}

#endif
