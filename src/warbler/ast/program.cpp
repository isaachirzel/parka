#include <warbler/ast/program.hpp>

#include <warbler/print.hpp>

namespace warbler::ast
{
	Program::Program(Array<Function>&& functions, Array<TypeDefinition>&& types) :
	_functions(functions),
	_types(types)
	{}

	Result<Program> Program::parse(TokenIterator& iter)
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

		return Program(std::move(functions), std::move(types));
	}

	void Program::print_tree(u32 depth) const
	{
		for (const auto& type: _types)
			type.print_tree(depth);

		for (const auto& function : _functions)
			function.print_tree(depth);
	}

	bool Program::validate()
	{
		for (auto& function : _functions)
		{
			const auto& function_name = function.name().text();

			auto iter = _context.symbols.find(function.name().text());

			if (iter != _context.symbols.end())
			{
				error_out(function.name().location()) << "duplicate function name: " << function_name << std::endl;
				return false;
			}
			
			_context.symbols.emplace(function.name().text(), semantics::Symbol { &function });
		}

		for (auto& function : _functions)
		{
			if (!function.validate(_context))
				return false;
		}

		return true;
	}
}