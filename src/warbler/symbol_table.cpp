#include <warbler/symbol_table.hpp>
#include <warbler/context.hpp>
#include <warbler/util/array.hpp>
#include <warbler/syntax.hpp>
#include <warbler/util/print.hpp>

namespace warbler
{
	String get_symbol_type_name(LocalSymbolType type)
	{
		switch (type)
		{
			case LocalSymbolType::Parameter:
				return "parameter";
			case LocalSymbolType::Variable:
				return "variable";
		}

		return "symbol";
	}

	String get_symbol_type_name(GlobalSymbolType type)
	{
		switch (type)
		{
			case GlobalSymbolType::Package:
				return "package";
			case GlobalSymbolType::Struct:
				return "struct";
			case GlobalSymbolType::Primitive:
				return "primitive";
			case GlobalSymbolType::Function:
				return "function";
		}

		return "symbol";
	}

	bool GlobalSymbolTable::add_symbol(GlobalSymbolData&& data)
	{
		auto previous_declaration = find(data.symbol());

		if (previous_declaration != nullptr)
		{
			auto message = get_symbol_type_name(data.type()) + " '" + data.symbol() + "' is already defined as a "
				+ get_symbol_type_name(previous_declaration->type());

			switch (data.type())
			{
				case GlobalSymbolType::Package:
					print_error(message);
					break;

				case GlobalSymbolType::Struct:
					print_error(data.struct_syntax().name(), message);
					break;

				case GlobalSymbolType::Primitive:
					print_error(message);
					break;

				case GlobalSymbolType::Function:
					print_error(data.function_syntax().name(), message);
					break;
			}

			switch (previous_declaration->type())
			{
				case GlobalSymbolType::Struct:
					print_note(previous_declaration->struct_syntax().name(), "Previous declaration here.");
					break;

				case GlobalSymbolType::Function:
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

		table._primitives = {
			PrimitiveContext("u8", PrimitiveType::UnsignedInteger, 1),
			PrimitiveContext("u16", PrimitiveType::UnsignedInteger, 2),
			PrimitiveContext("u32", PrimitiveType::UnsignedInteger, 4),
			PrimitiveContext("u64", PrimitiveType::UnsignedInteger, 8),
		};

		auto index = 0;

		for (const auto& primitive : table._primitives)
		{
			table._symbols.emplace(primitive.symbol(), GlobalSymbolData(primitive.symbol(), index, GlobalSymbolType::Primitive));
			index += 1;
		}

		bool success = true;

		for (const auto& package : syntax.packages())
		{
			auto scope = package.name() + "::";
			for (const auto& struct_def : package.structs())
			{
				auto struct_name = struct_def.name().text();
				auto symbol = scope + struct_name;

				if (!table.add_symbol(GlobalSymbolData(symbol, struct_def)))
					success = false;
			}

			for (const auto& function : package.functions())
			{
				auto name = function.name().text();
				auto symbol = scope + name;

				if (!table.add_symbol(GlobalSymbolData(symbol, function)))
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

	GlobalSymbolData *GlobalSymbolTable::resolve(const String& identifier)
	{
		for (i32 i = (i32)_current_package.size(); i >= 0; --i)
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

	bool LocalSymbolTable::add_parameter(const ParameterSyntax& parameter)
	{
		auto parameter_name = parameter.name().text();

		auto iter = _symbols.find(parameter_name);

		if (iter != _symbols.end())
		{
			print_error(parameter.name(), "The parameter name '" + parameter_name + "' is already being used in this parameter list");
			print_note(iter->second.parameter_syntax().name(), "Previous usage here.");
			return false;
		}

		_symbols.emplace(parameter_name, parameter);
		return true;
	}

	Result<LocalSymbolTable> LocalSymbolTable::generate(const FunctionSyntax& syntax)
	{
		auto success = true;

		LocalSymbolTable locals;

		for (const auto& parameter : syntax.signature().parameters())
		{
			success = success && locals.add_parameter(parameter);
		}

		Array<BlockSymbolTable*> scope;

		auto block = BlockSymbolTable::generate(syntax.body(), locals, scope);

		success = success && block;

		if (block)
		{
			locals._block_symbols = block.unwrap();
		}

		if (!success)
			return {};

		return locals;
	}

	bool BlockSymbolTable::add_variable(const VariableSyntax& variable, LocalSymbolTable& locals, Array<BlockSymbolTable*>& scope)
	{
		auto variable_name = variable.name().text();

		assert(!scope.empty());

		for (auto iter = scope.rbegin(); iter != scope.rend(); ++iter)
		{
			auto& block = **iter;

			auto *symbol = block.at(variable_name);

			if (symbol != nullptr)
			{
				print_error(variable.name(), "The declaration of variable '" + variable_name + "' shadows a previous declaration.");
				print_note(symbol->variable_syntax().name(), "Previous declaration here.");
				return false;
			}
		}

		auto parameter = locals.find_parameter(variable_name);

		if (parameter != nullptr)
		{
			print_error(variable.name(), "The declaration of variable '" + variable_name + "' shadows a parameter.");
			print_note(parameter->parameter_syntax().name(), "Previous declaration here.");
			return false;
		}

		_symbols.emplace(variable_name, LocalSymbolData(variable));
		return true;
	}

	Result<BlockSymbolTable> BlockSymbolTable::generate(const BlockStatementSyntax& syntax, LocalSymbolTable& locals, Array<BlockSymbolTable*>& scope)
	{
		BlockSymbolTable table;

		scope.push_back(&table);

		auto success = true;

		for (const auto& statement : syntax.statements())
		{
			switch (statement.type())
			{
				case StatementType::Declaration:
				{
					const auto& declaration = statement.declaration();
					success = success && table.add_variable(declaration.variable(), locals, scope);
					break;
				}

				case StatementType::Block:
				{
					auto block = generate(statement.block(), locals, scope);

					success = success & block;

					if (block)
					{
						table.add_block(block.unwrap());
					}
					break;
				}

				default:
					break;
			}
		}

		scope.pop_back();

		if (!success)
			return {};

		return table;
	}
}
