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
	enum class ValidationStatus
	{
		NotYetValidated,
		Validated,
		Invalid
	};

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
			const StructSyntax *_struct_syntax;
			const FunctionSyntax *_function_syntax;
			const ParameterSyntax *_parameter_syntax;
			const VariableSyntax *_variable_syntax;
		};

		usize _index = 0;
		SymbolType _type;
		ValidationStatus _validation = ValidationStatus::NotYetValidated;
		SymbolState _state = SymbolState::Destroyed;
		String _symbol;

	public:

		SymbolData(const PackageSyntax& syntax): _package_syntax(&syntax), _type(SymbolType::Package) {}
		SymbolData(const StructSyntax& syntax): _struct_syntax(&syntax), _type(SymbolType::Struct) {}
		SymbolData(const FunctionSyntax& syntax): _function_syntax(&syntax), _type(SymbolType::Function) {}
		SymbolData(const ParameterSyntax& syntax): _parameter_syntax(&syntax), _type(SymbolType::Parameter) {}
		SymbolData(const VariableSyntax& syntax): _variable_syntax(&syntax), _type(SymbolType::Variable) {}
		SymbolData(usize index, SymbolType symbol_type):
		_index(index),
		_type(symbol_type),
		_state(SymbolState::Initialized),
		_validation(ValidationStatus::Validated)
		{}
		SymbolData(SymbolData&&) = default;
		SymbolData(const SymbolData&) = default;
		~SymbolData() = default;

		void invalidate() { _validation = ValidationStatus::Invalid; }

		void validate(usize index)
		{
			_index = index;
			_state = SymbolState::Initialized;
			_validation = ValidationStatus::Validated;
		}

		auto& type() { return _type; }

		const auto& index() const { return _index; }
		const auto& type() const { return _type; }
		const auto& state() const { return _state; }
		const auto& validation_status() const { return _validation; }
		bool is_already_validated() const { return _validation != ValidationStatus::NotYetValidated; }
		bool is_not_yet_validated() const { return _validation == ValidationStatus::NotYetValidated; }
		bool is_valid() const { return _validation == ValidationStatus::Validated; }
		bool is_invalid() const { return _validation == ValidationStatus::Invalid; }

		const auto& struct_syntax() const { assert(_type == SymbolType::Struct); return *_struct_syntax; }
		const auto& function_syntax() const { assert(_type == SymbolType::Function); return *_function_syntax; }
		const auto& parameter_syntax() const { assert(_type == SymbolType::Parameter); return *_parameter_syntax; }
		const auto& variable_syntax() const { assert(_type == SymbolType::Variable); return *_variable_syntax; }
		const auto& symbol() const { return _symbol; }
	};

	class SymbolResolution
	{
		SymbolData& _data;
		String _symbol;

	public:

		SymbolResolution(SymbolData& data, const String& symbol):
		_data(data),
		_symbol(symbol)
		{}

		const auto& data() const { return _data; }
		const auto& symbol() const { return _symbol; }
	};

	class SymbolTable
	{
		Table<SymbolData> _symbols;
		Array<String> _current_scope;
		Array<StructContext>& _structs;
		Array<PrimitiveContext> &_primitives;
	
	public:

		SymbolTable(Array<StructContext>& structs, Array<PrimitiveContext>& primitives);
		
		bool add_symbols(const ProgramSyntax& syntax);
		void add_symbol(const String& symbol, const SymbolData& data);
		void push_package(const String& package) { _current_scope.push_back(package); }
		void pop_package() { _current_scope.pop_back(); }
		void set_scope_from_symbol(const String& symbol);

		String get_symbol(const String& identifier);
		usize add_validated_type(StructContext&& type);
		Result<SymbolResolution> resolve(const String& symbol);
		SymbolData& get(const String& symbol) { return _symbols.at(symbol); }

		auto begin() { return _symbols.begin(); }
		auto end() { return _symbols.end(); }
	};

	String get_symbol_type_name(SymbolType type);
}

#endif
