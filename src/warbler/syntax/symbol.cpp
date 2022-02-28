#include <warbler/syntax/symbol.hpp>

// local headers
#include <warbler/util/print.hpp>
#include <warbler/syntax/declaration.hpp>

// standard headers
#include <cstdlib>

namespace warbler::syntax
{
	Symbol::Symbol(const source::Location& location) :
	_location(location)
	{}

	Result<Symbol> Symbol::parse(lexicon::TokenIterator& iter)
	{
		if (iter->type() != lexicon::TokenType::Identifier)
		{
			print_parse_error(iter, "symbol");
			return {};
		}

		const auto& location = iter->location();

		iter += 1;

		return Symbol { location };
	}

	// bool Symbol::validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx)
	// {
	// 	#pragma message("Implement symbol checking for functions on validation")

	// 	auto *declaration = func_ctx.get_declaration(_text);

	// 	if (declaration == nullptr)
	// 	{
	// 		print_error(_location, "symbol '" + _text + "' is not declared in scope");
	// 		return false;
	// 	}

	// 	_type = &declaration->type();

	// 	return true;
	// }

	void Symbol::print_tree(u32 depth) const
	{
		print_branch(depth, _location.text());
	}
}