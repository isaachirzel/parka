#include <warbler/symbol_table.hpp>
#include <warbler/context.hpp>
#include <warbler/util/array.hpp>
#include <warbler/syntax.hpp>
#include <warbler/print.hpp>

namespace warbler
{
	Array<TypeDefinitionContext> _primitive_contexts =
	{
		TypeDefinitionContext("u8", PrimitiveContext { 1 }),
		TypeDefinitionContext("u16", PrimitiveContext { 2 }),
		TypeDefinitionContext("u32", PrimitiveContext { 4 }),
		TypeDefinitionContext("u64", PrimitiveContext { 8 }),
	};

	SymbolContext::SymbolContext(const PackageSyntax& syntax) :
	_package_syntax(&syntax),
	_type(SymbolType::Package),
	_context_index(-1)
	{}

	SymbolContext::SymbolContext(const FunctionSyntax& syntax) :
	_function_syntax(&syntax),
	_type(SymbolType::Function),
	_context_index(-1)
	{}

	SymbolContext::SymbolContext(const VariableSyntax& syntax) :
	_variable_syntax(&syntax),
	_type(SymbolType::Variable),
	_context_index(-1)
	{}

	SymbolContext::SymbolContext(const ParameterSyntax& syntax) :
	_parameter_syntax(&syntax),
	_type(SymbolType::Parameter),
	_context_index(-1)
	{}

	SymbolContext::SymbolContext(const TypeDefinitionSyntax& syntax) :
	_type_definition_syntax(&syntax),
	_type(SymbolType::TypeDefinition),
	_context_index(-1)
	{}


	// SymbolContext::SymbolContext(SymbolType type) :
	// _type(type)
	// {
	// 	switch (_type)
	// 	{
	// 		case SymbolType::Function:
	// 			new (&_function) Box<FunctionContext>();
	// 			break;

	// 		case SymbolType::Parameter:
	// 			new (&_parameter) Box<ParameterContext>();
	// 			break;

	// 		case SymbolType::Variable:
	// 			new (&_variable) Box<VariableContext>();
	// 			break;

	// 		case SymbolType::TypeDefinition:
	// 			new (&_type_definition) Box<TypeDefinitionContext>();				
	// 			break;
	// 	}
	// }

	// SymbolContext::SymbolContext(SymbolContext&& other) :
	// _type(other._type)
	// {
	// 	switch (_type)
	// 	{
	// 		case SymbolType::Function:
	// 			new (&_function) auto(std::move(other._function));
	// 			break;

	// 		case SymbolType::Parameter:
	// 			new (&_parameter) auto(std::move(other._parameter));
	// 			break;

	// 		case SymbolType::Variable:
	// 			new (&_variable) auto(std::move(other._variable));
	// 			break;

	// 		case SymbolType::TypeDefinition:
	// 			new (&_type_definition) auto(std::move(other._type_definition));
	// 			break;
	// 	}
	// }

	// SymbolContext::~SymbolContext()
	// {
	// 	switch (_type)
	// 	{
	// 		case SymbolType::Function:
	// 			_function.~Box();
	// 			break;

	// 		case SymbolType::Parameter:
	// 			_parameter.~Box();
	// 			break;

	// 		case SymbolType::Variable:
	// 			_variable.~Box();
	// 			break;

	// 		case SymbolType::TypeDefinition:
	// 			_type_definition.~Box();
	// 			break;
	// 	}
	// }

	static SymbolContext *get_symbol(Table<SymbolContext>& symbols, const String& symbol)
	{
		auto iter = symbols.find(symbol);

		return iter == symbols.end()
			? nullptr
			: &iter->second;
	}

	static String symbol_type_name(SymbolType type)
	{
		switch (type)
		{
			case SymbolType::Package:
				return "package";
			case SymbolType::TypeDefinition:
				return "type definition";
			case SymbolType::Function:
				return "function";
			case SymbolType::Parameter:
				return "parameter";
			case SymbolType::Variable:
				return "variable";
		}
	}

	static bool add_type_definition_symbol(Table<SymbolContext>& symbols, const TypeDefinitionSyntax& syntax)
	{
		auto symbol = syntax.name() + "::" + type_definition.name().token().text();
		auto previous_declaration = get_symbol(symbols, symbol);

		if (previous_declaration != nullptr)
		{
			// TODO: improve type name specification in error, and show location of previous declaration
			auto message = "symbol '" + symbol + "' is already defined");
			print_error(type_definition.name().token(), message);
			return false;
		}

		return true;
	}

	static bool add_package_symbols(Table<SymbolContext>& symbols, const PackageSyntax& syntax)
	{
		// this should never already be added, it is a programming mistake if so
		assert(get_symbol(symbols, syntax.name()) != nullptr);

		symbols.emplace(syntax.name(), syntax);

		auto success = true;

		for (const auto& type_definition : syntax.type_definitions())
		{
			if (!add_type_definition_symbol(symbols, type_definition))
				success = false;
		}

		return success;
	}

	bool SymbolTable::add_symbols(const ProgramSyntax& syntax)
	{
		bool success = true;

		for (const auto& package : syntax.packages())
		{
			_symbols.emplace(package.name(), package);

			if (!add_package_symbols(_symbols, package))
				success = false;
		}

		return success;
	}

	SymbolTable::SymbolTable() :
	_symbols()
	{
		// TODO: add predefined symbols
		// _symbols.reserve(_primitive_contexts.size());
		
		// for (usize i = 0; i < _primitive_contexts.size(); ++i)
		// {
		// 	const auto& primitive = _primitive_contexts[i];

		// 	_symbols.emplace(primitive.symbol(), SymbolContext(SymbolType::TypeDefinition));
		// }
	}

	void SymbolTable::push_scope(Table<SymbolContext>& scope)
	{
		_scopes.push_back(&scope);
	}

	void SymbolTable::pop_scope()
	{
		_scopes.pop_back();
	}

	void SymbolTable::add(const String& symbol, SymbolType type)
	{
		auto& current_scope = *_scopes.back();

		current_scope.emplace(symbol, SymbolContext(type));
	}

	SymbolContext *SymbolTable::resolve(const String& symbol)
	{
		// iterate from local scope to global scope
		for (auto iter = _scopes.rbegin(); iter != _scopes.rend(); ++iter)
		{
			auto& scope = **iter;
			auto context_location = scope.find(symbol);
			auto symbol_exists = context_location != scope.end();

			if (symbol_exists)
				return &context_location->second;
		}

		return nullptr;
	}
}
