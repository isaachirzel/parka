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
			return ERROR_ARGUMENT;
		}

		String text = String(iter->text());
			
		const auto& location = iter->location();

		iter += 1;

		return Identifier(location, std::move(text));
	}

	void Identifier::print_tree(u32 depth) const
	{
		std::cout << tree_branch(depth) << _text << '\n';
	}
}