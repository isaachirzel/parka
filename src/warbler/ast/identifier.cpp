#include <warbler/ast/identifier.hpp>

// local headers
#include <warbler/print.hpp>

// standard headers
#include <cstdlib>

namespace warbler::ast
{
	Identifier::Identifier(const Location& location, String&& text) :
	_location(location),
	_text(text)
	{}

	Result<Identifier> Identifier::parse(TokenIterator& iter)
	{
		if (iter->type() != TOKEN_IDENTIFIER)
		{
			parse_error(iter, "identifier");
			return {};
		}

		const auto& location = iter->location();
		String text = String(location.pos_ptr(), location.length());

		iter += 1;

		return Identifier { location, std::move(text) };
	}

	bool Identifier::validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx)
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

	void Identifier::print_tree(u32 depth) const
	{
		std::cout << tree_branch(depth) << _text << '\n';
	}
}