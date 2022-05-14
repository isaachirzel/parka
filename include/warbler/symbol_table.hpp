#ifndef WARBLER_SYMBOL_TABLE_HPP
#define WARBLER_SYMBOL_TABLE_HPP

#include <warbler/util/array.hpp>
#include <warbler/util/string.hpp>
#include <warbler/util/table.hpp>
#include <warbler/util/primitive.hpp>
#include <warbler/util/optional.hpp>
#include <warbler/util/box.hpp>
#include <warbler/type.hpp>
#include <warbler/context.hpp>
#include <cassert>

namespace warbler
{
	class DefinitionSyntax;
	class ProgramSyntax;
	class FunctionContext;
	class VariableContext;
	class ParameterContext;
	class TypeDefinitionContext;

	class SymbolReference
	{
		union
		{
			Array<PackageContext> *_packages;
			Array<TypeDefinitionContext> *_type_definitions;
			Array<FunctionContext> *_functions;
			Array<ParameterContext> _parameters;
			Array<VariableContext> *_variables;
		};

		SymbolType _type;

	public:

		SymbolReference(Array<FunctionContext>& functions, usize index);
		SymbolReference(Array<VariableContext>& variables, usize index);
		SymbolReference(Array<ParameterContext>& parameters, usize index);
		SymbolReference(Array<TypeDefinitionContext>& type_definitions, usize index);
		SymbolReference(Array<TypeDefinitionContext>& type_definitions, usize index);
	};

	class SymbolContext
	{
		union
		{
			Array<PackageContext> *_packages;
			Array<TypeDefinitionContext> *_type_definitions;
			Array<FunctionContext> *_functions;
			Array<ParameterContext> *_parameters;
			Array<VariableContext> *_variables;
		};

		union
		{
			const PackageSyntax *_package_syntax;
			const FunctionSyntax *_function_syntax;
			const TypeDefinitionSyntax *_type_definition_syntax;
			const ParameterSyntax *_parameter_syntax;
			const VariableSyntax *_variable_syntax;
		};

		i32 _context_index;
		SymbolType _type;
		
	public:

		SymbolContext(const PackageSyntax& syntax);
		SymbolContext(const TypeDefinitionSyntax& syntax);
		SymbolContext(const FunctionSyntax& syntax);
		SymbolContext(const ParameterSyntax& syntax);
		SymbolContext(const VariableSyntax& syntax);
		SymbolContext(SymbolContext&& other) = default;
		~SymbolContext() = default;

		void set(Array<PackageContext>& packages, usize index);
		void set(Array<TypeDefinitionContext>& type_definitions, usize index);
		void set(Array<FunctionContext>& functions, usize index);
		void set(Array<ParameterContext>& parameters, usize index);
		void set(Array<VariableContext>& variables, usize index);

		const auto& type() const { return _type; }

		const auto& function() const { assert(_type == SymbolType::Function && _context_index >= 0); return _functions[_context_index]; }
		const auto& function_syntax() const { assert(_type == SymbolType::Function); return _function_syntax; }

		const auto& variable() const { assert(_type == SymbolType::Variable && _context_index >= 0); return _variables[_context_index]; }
		const auto& variable_syntax() const { assert(_type == SymbolType::Variable); return _variable_syntax; }

		const auto& parameter() const { assert(_type == SymbolType::Parameter && _context_index >= 0); return _parameters[_context_index]; }
		const auto& parameter_syntax() const { assert(_type == SymbolType::Parameter); return _parameter_syntax; }

		const auto& type_definition() const { assert(_type == SymbolType::TypeDefinition && _context_index >= 0); return _type_definitions[_context_index]; }
		const auto& type_definition_syntax() const { assert(_type == SymbolType::TypeDefinition); return _type_definition_syntax; }

		const auto& package() const { assert(_type == SymbolType::Package && _context_index >= 0); return _packages[_context_index]; }
		const auto& package_syntax() const { assert(_type == SymbolType::Package); return _package_syntax; }
	};

	class SymbolTable
	{
		Table<SymbolContext> _symbols;
	
	public:
		SymbolTable();
		
		bool add_symbols(const ProgramSyntax& syntax);

		void push_scope(Table<SymbolContext>& symbols);
		void pop_scope();	

		void add(const String& symbol, SymbolType type);

		SymbolContext *resolve(const String& symbol);
		SymbolContext *resolve_relative(const String& symbol, const String& current_scope);
	};
}

#endif
