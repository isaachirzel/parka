#include <warbler/ast/module.hpp>

#include <warbler/print.hpp>

namespace warbler::ast
{
	Module::Module(Array<Function>&& functions, Array<TypeDefinition>&& types) :
	_functions(std::move(functions)),
	_types(std::move(types))
	{}

	Result<Module> Module::parse(TokenIterator& iter)
	{
		Array<Function> functions;
		Array<TypeDefinition> types;

		while (true)
		{
			switch (iter->type())
			{
				case TOKEN_FUNC:
				{
					auto function = Function::parse(iter);

					if (function.has_error())
						return function.error();

					functions.emplace_back(function.unwrap());
					continue;
				}
				case TOKEN_TYPE:
				{
					auto type = TypeDefinition::parse(iter);

					if (!type)
						return type.error();

					types.emplace_back(type.unwrap());
					continue;
				}
				case TOKEN_END_OF_FILE:
					break;

				default:
					parse_error(iter, "type or function definition");
					return ERROR_ARGUMENT;
			}

			break;
		}

		return Module(std::move(functions), std::move(types));
	}

	void Module::print_tree(u32 depth) const
	{
		for (const auto& type: _types)
			type.print_tree(depth);

		for (const auto& function : _functions)
			function.print_tree(depth);
	}

	bool Module::validate(const Array<String>& scope)
	{
		_context.scope = scope;
		// gettting valid types in module & generating symbols
		for (auto& type : _types)
		{
			type.generate_symbol(_context);
			const auto& type_name = type.name().text();

			if (_context.types.find(type_name) != _context.types.end())
			{
				error_out(type.name().location()) << "duplicate type " << type.name().text()
					<< " in module " << _context.qualified_scope();
				error_highlight(type.name().location());

				return false;
			}

			_context.types.insert(type_name);
		}

		std::cout << "validating types: " << _types.size() << std::endl;

		// checking if members of types are valid
		for (auto& type : _types)
		{
			if (!type.validate(_context))
				return false;
		}

		// checking for duplicate symbols
		for (auto& function : _functions)
		{
			const auto& function_name = function.name().text();

			if (_context.symbols.find(function_name) != _context.symbols.end())
			{
				error_out(function.name().location()) << "function '" << function_name << "' already defined in module '" << _context.qualified_scope() << '\'';
				error_highlight(function.name().location());

				return false;
			}

			_context.symbols.insert(function_name);
		}

		// validating functions
		for (auto& function : _functions)
		{
			if (!function.validate(_context))
				return false;
		}

		return true;
	}
}