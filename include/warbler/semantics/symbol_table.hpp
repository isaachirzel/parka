#ifndef WARBLER_SEMANTICS_SYMBOL_TABLE_HPP
#define WARBLER_SEMANTICS_SYMBOL_TABLE_HPP

#include <warbler/util/array.hpp>
#include <warbler/util/table.hpp>
#include <warbler/syntax/type/type_definition.hpp>

namespace warbler::semantics
{
	class Value
	{
	};

	class Type
	{
		Array<bool> _ptr_info;
		syntax::TypeDefinition *_definition;
	};

	enum class State
	{
		Uninitialized,
		Initialized,
		Deinitialized
	};

	class Attributes
	{
		// type
		Type _type;
		State _state;
		Value _value;
	};

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

// sed -i 's#validte(semantics::SymbolTablevalidate(semantics::ModuleContext\& mod_ctx, semantics::FunctionContext\& func_ctx) symbols)#validate(semantics::SymbolTable\& symbols)#g' $(find ../src -type f -name '*.cpp') $(find ../include -type f -name '*.hpp')

#endif
