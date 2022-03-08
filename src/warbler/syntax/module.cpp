#include <warbler/syntax/module.hpp>

#include <warbler/util/print.hpp>

namespace warbler::syntax
{
	Module::Module(Array<Function>&& functions, Array<Ptr<TypeDefinition>>&& types) :
	_functions(std::move(functions)),
	_types(std::move(types))
	{}

	Result<Module> Module::parse(lexicon::Token& token)
	{
		Array<Function> functions;
		Array<Ptr<TypeDefinition>> types;

		while (true)
		{
			switch (token.type())
			{
				case lexicon::TokenType::KeywordFunction:
				{
					auto function = Function::parse(token);

					if (!function)
						return {};

					functions.emplace_back(function.unwrap());
					continue;
				}
				case lexicon::TokenType::KeywordType:
				{
					auto type = TypeDefinition::parse(token);

					if (!type)
						return {};

					types.emplace_back(type.unwrap());
					continue;
				}
				case lexicon::TokenType::EndOfFile:
					break;

				default:
					print_parse_error(token, "type or function definition");
					return {};
			}

			break;
		}

		return Module(std::move(functions), std::move(types));
	}

	bool Module::validate(const String& module_name)
	{
		semantics::Context context(module_name, &_scope);
		
		for (auto& type : _types)
		{
			auto type_name = type->name().token().text();

			if (!context.has_symbol(type_name))
			{
				print_error(type->name().token(), "symbol '" + type->name().token().text() + "' is already defined in module '" + module_name + "'");

				return false;
			}

			context.add_type(type_name, type.raw_ptr());
		}

		// checking if members of types are valid
		for (auto& type : _types)
		{
			if (!type->validate(context))
				return false;
		}

		// checking for duplicate symbols
		for (auto& function : _functions)
		{
			auto function_name = function.name().token().text();

			if (!context.has_symbol(function_name))
			{
				print_error(function.name().token(), "symbol '" + function_name + "' is already defined in module '" + module_name + "'");

				return false;
			}

			context.add_function(function_name, &function);
		}

		// validating functions
		for (auto& function : _functions)
		{
			if (!function.validate(context))
				return false;
		}

		return true;
	}
}