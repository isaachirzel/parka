#include <warbler/ast/identifier.hpp>

#include <warbler/print.hpp>

namespace warbler::ast
{
	Identifier::Identifier(const Location& location) :
	_location(location),
	_text(location.text())
	{}

	Identifier::Identifier(String&& text) :
	_location(),
	_text(std::move(text))
	{}

	Identifier::Identifier() :
	_location(),
	_text()
	{}

	Result<Identifier> Identifier::parse(TokenIterator& iter)
	{
		if (iter->type() != TOKEN_IDENTIFIER)
			return {};

		const auto& location = iter->location();

		iter += 1;

		return Identifier { location };
	}

	void Identifier::print_tree(u32 depth) const
	{
		std::cout << tree_branch(depth) << _text << '\n';
}
}