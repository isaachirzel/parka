#include <warbler/ast/symbol.hpp>

// local headers
#include <warbler/print.hpp>
#include <warbler/ast/declaration.hpp>

// standard headers
#include <cstdlib>

namespace warbler::ast
{
	Symbol::Symbol(const Location& location) :
	_location(location),
	_text(location.text())
	{}

	Result<Symbol> Symbol::parse(TokenIterator& iter)
	{
		if (iter->type() != TOKEN_IDENTIFIER)
		{
			parse_error(iter, "identifier");
			return {};
		}

		const auto& location = iter->location();

		iter += 1;

		return Symbol { location };
	}

	bool Symbol::validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx)
	{
		#pragma message("Implement identifier checking for functions on validation")

		auto *declaration = func_ctx.get_declaration(_text);

		if (declaration == nullptr)
		{
			print_error(_location, "identifier '" + _text + "' is not declared in scope");
			return false;
		}

		_type_name = declaration->type_name();

		return true;
	}

	void Symbol::print_tree(u32 depth) const
	{
		std::cout << tree_branch(depth) << _text << '\n';
	}


}