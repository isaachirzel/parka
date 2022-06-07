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

	enum class LocalSymbolState
	{
		Initialized,
		Destroyed
	};

	class LocalSymbolData
	{
		union
		{
			const VariableSyntax *_variable_syntax;
			const ParameterSyntax *_parameter_syntax;
		};

		String _name;
		usize _index = 0;
		LocalSymbolType _type;
		LocalSymbolState _state = LocalSymbolState::Initialized;
		ValidationStatus _validation = ValidationStatus::NotYetValidated;

	public:

		LocalSymbolData(const VariableSyntax& syntax):
		_variable_syntax(&syntax),
		_name(syntax.name().text()),
		_type(LocalSymbolType::Variable)
		{}

		LocalSymbolData(const ParameterSyntax& syntax):
		_parameter_syntax(&syntax),
		_name(syntax.name().text()),
		_type(LocalSymbolType::Parameter)
		{}

		void validate(usize index)
		{
			_index = index;
			_validation = ValidationStatus::Valid;
		}
		
		void invalidate()
		{
			_validation = ValidationStatus::Invalid;
		}

		const auto& name() const { return _name; }
		const auto& parameter_syntax() const { assert(_type == LocalSymbolType::Parameter); return *_parameter_syntax; }
		const auto& variable_syntax() const { assert(_type == LocalSymbolType::Variable); return *_variable_syntax; }

		bool is_already_validated() const { return _validation != ValidationStatus::NotYetValidated; }
		bool is_not_yet_validated() const { return _validation == ValidationStatus::NotYetValidated; }
		bool is_valid() const { return _validation == ValidationStatus::Valid; }
		bool is_invalid() const { return _validation == ValidationStatus::Invalid; }
	};

	class LocalSymbolTable;

	class BlockSymbolTable
	{
		Array<Box<BlockSymbolTable>> _blocks;
		Table<LocalSymbolData> _symbols;

		bool add_variable(const VariableSyntax& variable, LocalSymbolTable& locals, Array<BlockSymbolTable*>& scope);
		
		void add_block(BlockSymbolTable&& table)
		{
			_blocks.emplace_back(std::move(table));
		};

	public:

		BlockSymbolTable() = default;
		BlockSymbolTable(BlockSymbolTable&& other) = default;
		BlockSymbolTable(const BlockSymbolTable&) = delete;

		static Result<BlockSymbolTable> generate(const BlockStatementSyntax& syntax, LocalSymbolTable& locals, Array<BlockSymbolTable*>& scope);

		LocalSymbolData *at(const String& name)
		{
			auto iter = _symbols.find(name);

			return iter != _symbols.end()
				? &iter->second
				: nullptr;
		}

		BlockSymbolTable& at(usize index)
		{
			assert(index < _blocks.size());
			return *_blocks[index];
		}

		BlockSymbolTable& operator=(const BlockSymbolTable&) = delete;
		BlockSymbolTable& operator=(BlockSymbolTable&&) = default;
	};

	class LocalSymbolTable
	{
		Table<LocalSymbolData> _symbols; // Parameters
		BlockSymbolTable _block_symbols;
		Array<usize> _scope;
		Array<VariableContext> _variables;
		Array<ParameterContext> _parameters;

		LocalSymbolTable() = default;

		bool add_parameter(const ParameterSyntax& parameter);

	public:

		static Result<LocalSymbolTable> generate(const FunctionSyntax& syntax);

		void push_scope(usize scope_index) { _scope.push_back(scope_index); }
		void pop_scope() { _scope.pop_back(); }

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

		LocalSymbolData *resolve(const String& name);
		LocalSymbolData *find_parameter(const String& name)
		{
			auto iter = _symbols.find(name);

			return iter != _symbols.end()
				? &iter->second
				: nullptr;
		}
		LocalSymbolData& get(const String& symbol) { return _symbols.at(symbol); }

		auto begin() { return _symbols.begin(); }
		auto end() { return _symbols.end(); }

		auto&& take_parameters() { return std::move(_parameters); }
		auto&& take_variables() { return std::move(_variables); }
	};

	class GlobalSymbolData
	{
		union
		{
			const StructSyntax *_struct_syntax;
			const FunctionSyntax *_function_syntax;
		};

		String _symbol;
		usize _index = 0;
		GlobalSymbolType _type;
		ValidationStatus _validation = ValidationStatus::NotYetValidated;

	public:

		static GlobalSymbolData package(const String& symbol)
		{
			return GlobalSymbolData(symbol, 0, GlobalSymbolType::Package);
		}

		GlobalSymbolData(const String& symbol, const StructSyntax& syntax): _struct_syntax(&syntax), _symbol(symbol), _type(GlobalSymbolType::Struct) {}
		GlobalSymbolData(const String& symbol, const FunctionSyntax& syntax): _function_syntax(&syntax), _symbol(symbol), _type(GlobalSymbolType::Function) {}
		GlobalSymbolData(const String& symbol, usize index, GlobalSymbolType symbol_type):
		_symbol(symbol),
		_index(index),
		_type(symbol_type),
		_validation(ValidationStatus::Valid)
		{
			switch (symbol_type)
			{
				case GlobalSymbolType::Struct:
					_struct_syntax = nullptr;
					break;

				case GlobalSymbolType::Function:
					_function_syntax = nullptr;
					break;

				default:
					break;
			}
		}

		GlobalSymbolData(GlobalSymbolData&&) = default;
		GlobalSymbolData(const GlobalSymbolData&) = default;
		~GlobalSymbolData() = default;

		void invalidate() { _validation = ValidationStatus::Invalid; }

		void validate(usize index)
		{
			_index = index;
			_validation = ValidationStatus::Valid;
		}

		auto& type() { return _type; }

		const auto& symbol() const { return _symbol; }
		const auto& index() const { return _index; }
		const auto& type() const { return _type; }
		const auto& validation_status() const { return _validation; }
		bool is_already_validated() const { return _validation != ValidationStatus::NotYetValidated; }
		bool is_not_yet_validated() const { return _validation == ValidationStatus::NotYetValidated; }
		bool is_valid() const { return _validation == ValidationStatus::Valid; }
		bool is_invalid() const { return _validation == ValidationStatus::Invalid; }

		const auto& struct_syntax() const { assert(_type == GlobalSymbolType::Struct); return *_struct_syntax; }
		const auto& function_syntax() const { assert(_type == GlobalSymbolType::Function); return *_function_syntax; }
	};

	class GlobalSymbolTable
	{
		Table<GlobalSymbolData> _symbols;
		Array<StructContext> _structs;
		Array<FunctionContext> _functions;
		Array<PrimitiveContext> _primitives;
		Array<String> _current_package;
	
		GlobalSymbolTable() = default;

		bool add_symbol(GlobalSymbolData&& data);

	public:

		static Result<GlobalSymbolTable> generate(const ProgramSyntax& syntax);

		void push_package(const String& package) { _current_package.push_back(package); }
		void pop_package() { _current_package.pop_back(); }
		void set_scope_from_symbol(const String& symbol);

		String get_symbol(const String& identifier);
		usize add_validated_struct(StructContext&& struct_def);
		usize add_validated_function(FunctionContext&& function);
		GlobalSymbolData *resolve(const String& symbol);
		GlobalSymbolData& get(const String& symbol) { return _symbols.at(symbol); }
		GlobalSymbolData *find(const String& symbol)
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
			assert(index < _primitives.size());
			return _primitives[index];
		}

		auto begin() { return _symbols.begin(); }
		auto end() { return _symbols.end(); }

		auto&& take_structs() { return std::move(_structs); }
		auto&& take_primitives() { return std::move(_primitives); }
		auto&& take_functions() { return std::move(_functions); }
	};

	String get_symbol_type_name(GlobalSymbolType type);
}

#endif
