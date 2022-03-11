#include <warbler/semantics/symbol_table.hpp>

namespace warbler::semantics
{
	SymbolTable::SymbolTable(const String& module_name, ScopeContext *module_scope) :
	_module_name(module_name),
	_scopes({ module_scope })
	{}

	void SymbolTable::push_scope(ScopeContext *scope)
	{
	}

	void SymbolTable::pop_scope()
	{
	}

	bool SymbolTable::has_symbol(const String& symbol)
	{
	}

	void SymbolTable::add_parameter(const String& name, syntax::Parameter *parameter)
	{
	}

	void SymbolTable::add_function(const String& name, syntax::Function *function)
	{
	}

	void SymbolTable::add_variable(const String& name, syntax::Variable *declaration)
	{
	}

	void SymbolTable::add_type(const String& name, syntax::TypeDefinition *type)
	{
		const ScopeContext& module_scope = *_scopes[0];
	}
	
	SymbolContext *SymbolTable::find(const String& symbol)
	{
	}
}
