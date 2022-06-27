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
		Valid,
		Invalid
	};

	class SymbolData
	{
		union
		{
			const StructSyntax *_struct_syntax;
			const FunctionSyntax *_function_syntax;
			const VariableSyntax *_variable_syntax;
			const ParameterSyntax *_parameter_syntax;
		};

		String _symbol;
		usize _index = 0;
		SymbolType _type;
		ValidationStatus _validation = ValidationStatus::NotYetValidated;
		bool _is_destroyed = false;

	private:

		SymbolData(const String& symbol):
		_symbol(symbol),
		_type(SymbolType::Package),
		_validation(ValidationStatus::Valid)
		{}

	public:

		static SymbolData package(const String& symbol)
		{
			return SymbolData(symbol);
		}

		SymbolData(const String& symbol, const StructSyntax& syntax):
		_struct_syntax(&syntax),
		_symbol(symbol),
		_type(SymbolType::Struct)
		{}

		SymbolData(const String& symbol, const FunctionSyntax& syntax):
		_function_syntax(&syntax),
		_symbol(symbol),
		_type(SymbolType::Function)
		{}

		SymbolData(const VariableSyntax& syntax):
		_variable_syntax(&syntax),
		_symbol(syntax.name().text()),
		_type(SymbolType::Variable)
		{}

		SymbolData(const ParameterSyntax& syntax):
		_parameter_syntax(&syntax),
		_symbol(syntax.name().text()),
		_type(SymbolType::Parameter)
		{}

		SymbolData(const char *symbol, usize index, SymbolType type):
		_symbol(symbol),
		_index(index),
		_type(type),
		_validation(ValidationStatus::Valid)
		{}

		SymbolData(SymbolData&&) = default;
		SymbolData(const SymbolData&) = default;
		~SymbolData() = default;

		void invalidate() { _validation = ValidationStatus::Invalid; }

		void validate(usize index)
		{
			_index = index;
			_validation = ValidationStatus::Valid;
		}

		void destroy() { _is_destroyed = true; }
		void reinitialize() { _is_destroyed = false; }

		const auto& type() { return _type; }
		const auto& symbol() const { return _symbol; }
		const auto& index() const {assert(_validation == ValidationStatus::Valid); return _index; }
		const auto& type() const { return _type; }
		const auto& validation_status() const { return _validation; }
		bool is_already_validated() const { return _validation != ValidationStatus::NotYetValidated; }
		bool is_not_yet_validated() const { return _validation == ValidationStatus::NotYetValidated; }
		bool is_valid() const { return _validation == ValidationStatus::Valid; }
		bool is_invalid() const { return _validation == ValidationStatus::Invalid; }
		bool is_destroyed() const { return _is_destroyed; }

		const auto& struct_syntax() const { assert(_type == SymbolType::Struct); return *_struct_syntax; }
		const auto& function_syntax() const { assert(_type == SymbolType::Function); return *_function_syntax; }
		const auto& variable_syntax() const { assert(_type == SymbolType::Variable); return *_variable_syntax; }
		const auto& parameter_syntax() const { assert(_type == SymbolType::Parameter); return *_parameter_syntax; }
	};

	struct AddSymbolResult
	{
		bool success;
		SymbolData& data;
	};

	class GlobalSymbolTable
	{
		Table<SymbolData> _symbols;
		Array<StructContext> _structs;
		Array<FunctionContext> _functions; 
		Array<String> _current_package;
	
		GlobalSymbolTable() = default;

		bool add_symbol(SymbolData&& data);

	public:

		static Result<GlobalSymbolTable> generate(const ProgramSyntax& syntax);

		void push_package(const String& package) { _current_package.push_back(package); }
		void pop_package() { _current_package.pop_back(); }
		void set_scope_from_symbol(const String& symbol);

		String get_symbol(const String& identifier);
		usize add_validated_struct(StructContext&& struct_def);
		usize add_validated_function(FunctionContext&& function);

		SymbolData *resolve(const String& symbol);
		SymbolData& get(const String& symbol) { return _symbols.at(symbol); }
		SymbolData *find(const String& symbol)
		{
			auto iter = _symbols.find(symbol);
			auto *ptr = iter != _symbols.end()
				? &iter->second
				: nullptr;

			return ptr;
		}

		const auto& get_struct(usize index)
		{
			assert(index < _structs.size());
			return _structs[index];
		}

		const auto& get_primitive(usize index)
		{
			assert(index < primitive_count);
			return primitives[index];
		}

		auto begin() { return _symbols.begin(); }
		auto end() { return _symbols.end(); }

		auto&& take_structs() { return std::move(_structs); }
		auto&& take_functions() { return std::move(_functions); }
	};

	class BlockSymbolTable
	{		
	private:

		Table<SymbolData> _symbols;

	public:

		BlockSymbolTable() = default;
		BlockSymbolTable(BlockSymbolTable&& other) = default;
		BlockSymbolTable(const BlockSymbolTable&) = delete;

		SymbolData *at(const String& name)
		{
			auto iter = _symbols.find(name);

			return iter != _symbols.end()
				? &iter->second
				: nullptr;
		}

		AddSymbolResult add_variable(const VariableSyntax& variable);

		BlockSymbolTable& operator=(const BlockSymbolTable&) = delete;
		BlockSymbolTable& operator=(BlockSymbolTable&&) = default;
	};

	class FunctionSymbolTable
	{
		Table<SymbolData> _symbols;
		Array<BlockSymbolTable> _blocks;
		Array<VariableContext> _variables;
		Array<ParameterContext> _parameters;
		GlobalSymbolTable *_globals;

	public:

		FunctionSymbolTable(GlobalSymbolTable& globals):
		_globals(&globals)
		{}

		AddSymbolResult add_parameter(const ParameterSyntax& parameter);
		AddSymbolResult add_variable(const VariableSyntax& syntax)
		{
			assert(!_blocks.empty());
			return _blocks.back().add_variable(syntax);
		};

		usize add_validated_variable(VariableContext&& variable)
		{
			auto index = _variables.size();

			_variables.emplace_back(std::move(variable));

			return index;
		}

		usize add_validated_parameter(ParameterContext&& parameter)
		{
			auto index = _parameters.size();

			_parameters.emplace_back(std::move(parameter));

			return index;
		}

		SymbolData *find_variable(const String& name);
		SymbolData *find_parameter(const String& name)
		{
			auto iter = _symbols.find(name);

			return iter != _symbols.end()
				? &iter->second
				: nullptr;
		}

		SymbolData *resolve(const String& identifier);

		void push_block() { _blocks.push_back({}); }
		void pop_block() { _blocks.pop_back(); }

		SymbolData& get(const String& symbol) { return _symbols.at(symbol); }

		auto begin() { return _symbols.begin(); }
		auto end() { return _symbols.end(); }

		auto&& take_parameters() { return std::move(_parameters); }
		auto&& take_variables() { return std::move(_variables); }

		GlobalSymbolTable& globals() const { return *_globals; }
	};

	String get_symbol_type_name(SymbolType type);
}

#endif
