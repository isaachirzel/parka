#include <warbler/ast/name.hpp>

#include <warbler/print.hpp>

namespace warbler::ast
{
	Name::Name(String&& text, const Location& location) :
	_text(std::move(text)),
	_location(location)
	{}

	Name::Name() :
	_text(),
	_location()
	{}

	Result<Name> Name::parse(TokenIterator& iter)
	{
		if (iter->type() != TOKEN_IDENTIFIER)
			return {};

		const auto& location = iter->location();

		iter += 1;

		return Name { String { location.pos_ptr(), location.length() }, location };
	}

	void Name::print_tree(u32 depth) const
	{
		std::cout << tree_branch(depth) << _text << '\n';
}
}