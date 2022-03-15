#include <warbler/semantics/symbol_table.hpp>

namespace warbler::semantics
{
	SymbolTable::SymbolTable(Table<Symbol>& module_scope) :
	_scopes({ &module_scope })
	{}

	void SymbolTable::push_scope(Table<Symbol>& scope)
	{
		_scopes.push_back(&scope);
	}

	void SymbolTable::pop_scope()
	{
		_scopes.pop_back();
	}

	void SymbolTable::add_function(Function&& function)
	{
		auto& current_scope = *_scopes.back();

		current_scope.emplace(function.symbol(), std::move(function));
	}

	void SymbolTable::add_parameters(Array<Parameter>& parameters)
	{
		auto& scope = *_scopes.back();

		for (auto& parameter : parameters)
		{
			scope.emplace(parameter.symbol(), parameter);
		}
	}

	void SymbolTable::add_variable(Variable&& variable)
	{
		auto& current_scope = *_scopes.back();

		current_scope.emplace(variable.name(), std::move(variable));
	}

	void SymbolTable::add_type(Definition&& type)
	{
		auto& module_scope = *_scopes[0];

		module_scope.emplace(type.symbol(), std::move(type));
	}
	
	Symbol *SymbolTable::resolve(const String& symbol)
	{
		for (long i = _scopes.size() - 1; i >= 0; --i)
		{
			auto& scope = *_scopes[i];

			auto iter = scope.find(symbol);

			if (iter != scope.end())
			{
				return &iter->second;
			}
		}

		return nullptr;
	}

	String SymbolTable::get_symbol(const String& name)
	{
		usize size = name.size();

		for (const auto *str : _lexical_scope)
			size += str->size() + 2;

		String out;

		out.reserve(size);

		for (const auto *str : _lexical_scope)
		{
			out += *str;
			out += "::";
		}

		out += name;

		return out;
	}
}
