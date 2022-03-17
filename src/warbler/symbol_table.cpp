#include <warbler/symbol_table.hpp>

#include <warbler/context.hpp>

namespace warbler
{
	SymbolTable::SymbolTable(Table<SymbolContext>& module_scope) :
	_scope({ &module_scope })
	{}

	void SymbolTable::push_scope(Table<SymbolContext>& scope)
	{
		_scope.push_back(&scope);
	}

	void SymbolTable::pop_scope()
	{
		_scope.pop_back();
	}

	void SymbolTable::add_function(FunctionContext& function)
	{
		auto& current_scope = *_scope.back();

		current_scope.emplace(function.name().symbol(), SymbolContext(function));
	}

	void SymbolTable::add_parameters(Array<ParameterContext>& parameters)
	{
		auto& scope = *_scope.back();

		for (auto& parameter : parameters)
		{
			scope.emplace(parameter.symbol(), SymbolContext(parameter));
		}
	}

	void SymbolTable::add_variable(VariableContext& variable)
	{
		auto& current_scope = *_scope.back();

		current_scope.emplace(variable.name(), SymbolContext(variable));
	}

	void SymbolTable::add_type(TypeDefinitionContext& type)
	{
		_scope[0]->emplace(type.symbol(), SymbolContext(type));
	}
	
	SymbolContext *SymbolTable::resolve(const String& symbol)
	{
		for (long i = _scope.size() - 1; i >= 0; --i)
		{
			auto& scope = *_scope[i];

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

		for (const auto *str : _package)
			size += str->size() + 2;

		String out;

		out.reserve(size);

		for (const auto *str : _package)
		{
			out += *str;
			out += "::";
		}

		out += name;

		return out;
	}
}
