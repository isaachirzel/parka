#include <warbler/ast/program.hpp>

#include <warbler/print.hpp>

namespace warbler
{
	Program::Program(std::vector<Function>&& functions) :
	_functions(functions)
	{}

	Result<Program> Program::parse(TokenIterator& iter)
	{
		std::vector<Function> functions;

		while (iter->type() == TOKEN_FUNC)
		{
			auto function = Function::parse(iter);

			if (function.has_error())
				return function.error();

			functions.emplace_back(function.unwrap());
		}

		return Program(std::move(functions));
	}

	void Program::print_tree(u32 depth) const
	{
		for (const auto& function : _functions)
			function.print_tree(depth);
	}

	bool Program::validate()
	{
		for (auto& function : _functions)
		{
			const auto& function_name = function.name().text();		
			auto iter = _symbols.find(function.name().text());

			if (iter != _symbols.end())
			{
				error_out(function.name().location()) << "duplicate function name: " << function_name << std::endl;
				return false;
			}
			
			_symbols.emplace(function.name().text(), Symbol { &function });
		}

		for (auto& function : _functions)
		{
			if (!function.validate(_types, _symbols))
				return false;
		}

		return true;
	}
}