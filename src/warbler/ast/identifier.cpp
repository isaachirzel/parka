#include <warbler/ast/identifier.hpp>

#include <warbler/print.hpp>

namespace warbler::ast
{
	Identifier::Identifier(String&& text, const Location& location) :
	_text(std::move(text)),
	_location(location)
	{}

	Identifier::Identifier() :
	_text(),
	_location()
	{}

	Result<Identifier> Identifier::parse(TokenIterator& iter)
	{
		if (iter->type() != TOKEN_IDENTIFIER)
			return {};

		const auto& location = iter->location();

		iter += 1;

		return Identifier { String { location.pos_ptr(), location.length() }, location };
	}

	void Identifier::print_tree(u32 depth) const
	{
		std::cout << tree_branch(depth) << _text << '\n';
}
}