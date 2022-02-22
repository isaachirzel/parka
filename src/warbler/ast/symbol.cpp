#include <warbler/ast/symbol.hpp>

// local headers
#include <warbler/print.hpp>

// standard headers
#include <cstdlib>

namespace warbler::ast
{
	Symbol::Symbol(const Location& location, String&& text) :
	_location(location),
	_text(text)
	{}

	Result<Symbol> Symbol::parse(TokenIterator& iter)
	{
		if (iter->type() != TOKEN_IDENTIFIER)
		{
			parse_error(iter, "identifier");
			return {};
		}

		const auto& location = iter->location();
		String text = String(location.pos_ptr(), location.length());

		iter += 1;

		return Symbol { location, std::move(text) };
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

		return true;
	}

	void Symbol::print_tree(u32 depth) const
	{
		std::cout << tree_branch(depth) << _text << '\n';
	}

	Typename *Symbol::get_type(semantics::ModuleContext& mod_ctx) const
	{
		throw std::runtime_error("Typename::" + String(__func__) + " is not implemented yet");
	}
}