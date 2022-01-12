#include <warbler/ast/program.hpp>

// standard headers
#include <cstdlib>
#include <cassert>

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

	void Program::print_tree(u32 depth = 0) const
	{
		for (const auto& function : _functions)
			function.print_tree(depth);
	}
}