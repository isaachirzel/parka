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

	// void Module::print_tree(u32 depth) const
	// {
	// 	for (const auto& type: _types)
	// 		type->print_tree(depth);

	// 	for (const auto& function : _functions)
	// 		function.print_tree(depth);
	// }

	// bool Module::validate(const String& module_name)
	// {
	// 	_context.name = module_name;
		
	// 	for (auto& type : _types)
	// 	{
	// 		const auto& type_name = type->name().text();

	// 		if (_context.types.find(type_name) != _context.types.end())
	// 		{
	// 			print_error(type->name().token(), "duplicate type " + type->name().text() + " in module '" + module_name + "'");

	// 			return false;
	// 		}

	// 		_context.types[type_name] = type.raw_ptr();
	// 	}

	// 	// checking if members of types are valid
	// 	for (auto& type : _types)
	// 	{
	// 		if (!type->validate(_context))
	// 			return false;
	// 	}

	// 	// checking for duplicate symbols
	// 	for (auto& function : _functions)
	// 	{
	// 		const auto& function_name = function.name().text();

	// 		if (_context.functions.find(function_name) != _context.functions.end())
	// 		{
	// 			print_error(function.name().token(), "function '" + function_name + "' is already defined in module '" + module_name + "'");

	// 			return false;
	// 		}

	// 		_context.functions[function_name] = &function;
	// 	}

	// 	// validating functions
	// 	for (auto& function : _functions)
	// 	{
	// 		if (!function.validate(_context))
	// 			return false;
	// 	}

	// 	return true;
	// }
}