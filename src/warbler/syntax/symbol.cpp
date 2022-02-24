#include <warbler/syntax//symbol.hpp>

// local headers
#include <warbler/util/print.hpp>
#include <warbler/syntax//declaration.hpp>

// standard headers
#include <cstdlib>

namespace warbler::syntax
{
	Symbol::Symbol(const Location& location) :
	_location(location),
	_text(location.text())
	{}

	Result<Symbol> Symbol::parse(lexicon::TokenIterator& iter)
	{
		if (iter->type() != lexicon::TOKEN_IDENTIFIER)
		{
			print_parse_error(iter, "identifier");
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

		_type = &declaration->type();

		return true;
	}

	void Symbol::print_tree(u32 depth) const
	{
		std::cout << tree_branch(depth) << _text << '\n';
	}


}