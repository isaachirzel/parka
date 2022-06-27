#include <warbler/symbol_table.hpp>
#include <warbler/context.hpp>
#include <warbler/util/array.hpp>
#include <warbler/syntax.hpp>
#include <warbler/util/print.hpp>

namespace warbler
{
	String get_symbol_type_name(SymbolType type)
	{
		switch (type)
		{
			case SymbolType::Package:
				return "package";

			case SymbolType::Struct:
				return "struct";

			case SymbolType::Primitive:
				return "primitive";

			case SymbolType::Function:
				return "function";

			case SymbolType::Variable:
				return "variable";

			case SymbolType::Parameter:
				return "parameter";

			default:
				throw std::invalid_argument("Invalid symbol type for type name");
		}
	}

	bool GlobalSymbolTable::add_symbol(SymbolData&& data)
	{
		auto previous_declaration = find(data.symbol());

		if (previous_declaration != nullptr)
		{
			auto message = get_symbol_type_name(data.type()) + " '" + data.symbol() + "' is already defined as a "
				+ get_symbol_type_name(previous_declaration->type());

			switch (data.type())
			{
				case SymbolType::Package:
					print_error(message);
					break;

				case SymbolType::Struct:
					print_error(data.struct_syntax().name(), message);
					break;

				case SymbolType::Primitive:
					print_error(message);
					break;

				case SymbolType::Function:
					print_error(data.function_syntax().name(), message);
					break;

				default:
					throw std::runtime_error("Invalid type");
			}

			switch (previous_declaration->type())
			{
				case SymbolType::Struct:
					print_note(previous_declaration->struct_syntax().name(), "Previous declaration here.");
					break;

				case SymbolType::Function:
					print_note(previous_declaration->function_syntax().name(), "Previous declaration here.");
					break;

				default:
					break;
			}

			return false;
		}

		_symbols.emplace(data.symbol(), data);

		return true;
	}

	Result<GlobalSymbolTable> GlobalSymbolTable::generate(const ProgramSyntax& syntax)
	{
		GlobalSymbolTable table;

		auto& symbols = table._symbols;

		symbols.emplace("u8", SymbolData("u8", U8_INDEX, SymbolType::Primitive));
		symbols.emplace("u16", SymbolData("u16", U16_INDEX, SymbolType::Primitive));
		symbols.emplace("u32", SymbolData("u32", U32_INDEX, SymbolType::Primitive));
		symbols.emplace("u64", SymbolData("u64", U64_INDEX, SymbolType::Primitive));

		symbols.emplace("i8", SymbolData("i8", I8_INDEX, SymbolType::Primitive));
		symbols.emplace("i16", SymbolData("i16", I16_INDEX, SymbolType::Primitive));
		symbols.emplace("i32", SymbolData("i32", I32_INDEX, SymbolType::Primitive));
		symbols.emplace("i64", SymbolData("i64", I64_INDEX, SymbolType::Primitive));

		symbols.emplace("f32", SymbolData("f32", F32_INDEX, SymbolType::Primitive));
		symbols.emplace("f64", SymbolData("f64", F64_INDEX, SymbolType::Primitive));

		symbols.emplace("bool", SymbolData("bool", BOOL_INDEX, SymbolType::Primitive));
		symbols.emplace("char", SymbolData("char", CHAR_INDEX, SymbolType::Primitive));

		bool success = true;

		for (const auto& package : syntax.packages())
		{
			auto scope = package.name() + "::";

			for (const auto& struct_def : package.structs())
			{
				auto struct_name = struct_def.name().text();
				auto symbol = scope + struct_name;

				if (!table.add_symbol(SymbolData(symbol, struct_def)))
					success = false;
			}

			for (const auto& function : package.functions())
			{
				auto name = function.name().text();
				auto symbol = scope + name;

				if (!table.add_symbol(SymbolData(symbol, function)))
					success = false;
			}
		}

		if (!success)
			return {};

		return table;
	}

	static String create_symbol(const Array<String>& packages, usize count, const String& identifier)
	{
		String symbol;

		symbol.reserve(128);

		for (usize i = 0; i < count; ++i)
		{
			symbol += packages[i];
			symbol += "::";
		}

		symbol += identifier;

		return symbol;
	}

	void GlobalSymbolTable::set_scope_from_symbol(const String& symbol)
	{
		assert(!symbol.empty());

		_current_package.clear();

		String tmp;

		tmp.reserve(64);

		// split symbol by '::'
		for (usize i = 0; i < symbol.size(); ++i)
		{
			if (symbol[i] == ':')
			{
				assert(symbol[i + 1] == ':');
				_current_package.push_back(tmp);
				tmp.clear();
				i += 1;
				continue;
			}

			tmp += symbol[i];
		}
	}

	// TODO: make this safe
	String GlobalSymbolTable::get_symbol(const String& identifier)
	{
		return create_symbol(_current_package, _current_package.size(), identifier);
	}

	SymbolData *GlobalSymbolTable::resolve(const String& identifier)
	{
		for (i32 i = static_cast<i32>(_current_package.size()); i >= 0; --i)
		{
			auto symbol = create_symbol(_current_package, i, identifier);
			auto iter = _symbols.find(symbol);

			if (iter != _symbols.end())
				return &iter->second;
		}

		return nullptr;
	}

	usize GlobalSymbolTable::add_validated_struct(StructContext&& type)
	{
		auto index = _structs.size();
		
		_structs.emplace_back(std::move(type));

		return index;
	}

	usize GlobalSymbolTable::add_validated_function(FunctionContext&& function)
	{
		auto index = _functions.size();

		_functions.emplace_back(std::move(function));

		return index;
	}

	AddSymbolResult FunctionSymbolTable::add_parameter(const ParameterSyntax& syntax)
	{
		auto name = syntax.name().text();
		auto result = _symbols.emplace(name, syntax);
		auto success = result.second;
		auto& symbol_data = result.first->second;

		if (!success) // Failed to emplace
		{
			print_error(syntax.name(), "A parameter with the name '" + name + "' already exists in this scope.");
			print_note(symbol_data.parameter_syntax().name(), "Previous usage here.");

			new (&symbol_data) auto(SymbolData(syntax));
		}

		return { success, symbol_data };
	}

	AddSymbolResult BlockSymbolTable::add_variable(const VariableSyntax& syntax)
	{
		auto name = syntax.name().text();
		auto result = _symbols.emplace(name, syntax);
		auto success = result.second;
		auto& symbol_data = result.first->second;

		if (!success) // Failed to emplace
		{
			print_error(syntax.name(), "A variable with the name '" + name + "' already exists in this parameter list.");
			print_note(symbol_data.variable_syntax().name(), "Previous usage here.");

			new (&symbol_data) auto(SymbolData(syntax));
		}

		return { success, symbol_data };
	}

	SymbolData *FunctionSymbolTable::find_variable(const String& identifier)
	{
		for (i32 i = static_cast<i32>(_blocks.size()) - 1; i >= 0; --i)
		{
			auto& block = _blocks[i];
			auto *res = block.at(identifier);

			if (res)
				return res;
		}

		return nullptr;
	}

	static inline bool contains_semicolon(const String& identifier)
	{
		for (char c : identifier)
		{
			if (c == ':')
				return true;
		}

		return false;
	}

	SymbolData *FunctionSymbolTable::resolve(const String& identifier)
	{
		if (!contains_semicolon(identifier))
		{
			auto *variable = find_variable(identifier);

			if (variable)
				return variable;

			auto *parameter = find_parameter(identifier);

			if (parameter)
				return parameter;
		}

		auto *global = _globals->resolve(identifier);

		if (global)
			return global;

		return nullptr;
	}
}
