#ifndef WARBLER_SYMBOL_TABLE_HPP
#define WARBLER_SYMBOL_TABLE_HPP

#include <warbler/util/array.hpp>
#include <warbler/util/string.hpp>
#include <warbler/util/table.hpp>
#include <warbler/util/primitive.hpp>
#include <warbler/util/optional.hpp>
#include <warbler/util/box.hpp>
#include <warbler/type.hpp>
#include <warbler/syntax.hpp>
#include <warbler/context.hpp>
#include <cassert>

namespace warbler
{
	enum class SymbolState
	{
		Initialized,
		Destroyed
	};

	class SymbolData
	{
		union
		{
			const PackageSyntax *_package_syntax;
			const TypeSyntax *_type_syntax;
			const FunctionSyntax *_function_syntax;
			const ParameterSyntax *_parameter_syntax;
			const VariableSyntax *_variable_syntax;
		};

		usize _index = 0;
		SymbolType _type;
		SymbolState _state = SymbolState::Destroyed;
		bool _is_validated = false;

	public:

		SymbolData(const PackageSyntax& syntax): _package_syntax(&syntax), _type(SymbolType::Package) {}
		SymbolData(const TypeSyntax& syntax): _type_syntax(&syntax), _type(SymbolType::Type) {}
		SymbolData(const FunctionSyntax& syntax): _function_syntax(&syntax), _type(SymbolType::Function) {}
		SymbolData(const ParameterSyntax& syntax): _parameter_syntax(&syntax), _type(SymbolType::Parameter) {}
		SymbolData(const VariableSyntax& syntax): _variable_syntax(&syntax), _type(SymbolType::Variable) {}
		SymbolData(usize index, SymbolType symbol_type):
		_index(index),
		_type(symbol_type),
		_state(SymbolState::Initialized),
		_is_validated(true)
		{}
		SymbolData(SymbolData&&) = default;
		SymbolData(const SymbolData&) = default;
		~SymbolData() = default;

		void validate(usize index)
		{
			_index = index;
			_state = SymbolState::Initialized;
			_is_validated = true;
		}

		auto& type() { return _type; }

		const auto& index() const { return _index; }
		const auto& type() const { return _type; }
		const auto& state() const { return _state; }
		const auto& is_validated() const { return _is_validated; }

		const auto& type_syntax() const { assert(_type == SymbolType::Type); return *_type_syntax; }
		const auto& function_syntax() const { assert(_type == SymbolType::Function); return *_function_syntax; }
		const auto& parameter_syntax() const { assert(_type == SymbolType::Parameter); return *_parameter_syntax; }
		const auto& variable_syntax() const { assert(_type == SymbolType::Variable); return *_variable_syntax; }

	};

	class SymbolTable
	{
		Table<SymbolData> _symbols;
		Array<TypeContext>& _types;
	
	public:

		SymbolTable(Array<TypeContext>& types);
		
		bool add_symbols(const ProgramSyntax& syntax);
		void add_symbol(const String& symbol, const SymbolData& data);

		// usize validate_function(FunctionContext&& function);
		usize add_validated_type(TypeContext&& type);
		// usize validate_parameter(ParameterContext&& parameter);
		// usize validate_variable(VariableContext&& variable);

		SymbolData *resolve(const String& current_scope, const String& symbol);
		SymbolData *resolve_relative(const String& symbol, const String& current_scope);

	
	};
}

#endif
