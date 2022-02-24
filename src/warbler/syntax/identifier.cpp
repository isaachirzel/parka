#include <warbler/syntax//identifier.hpp>

#include <warbler/util/print.hpp>
#include <warbler/

namespace warbler::syntax
{
	using source::Location;
	using lexicon::lexicon::TokenIterator;

	Identifier::Identifier(const Location& location) :
	_location(location)
	{}

	Result<Identifier> Identifier::parse(lexicon::TokenIterator& iter)
	{
		if (iter->type() != lexicon::TOKEN_IDENTIFIER)
			return {};

		const auto& location = iter->location();
		auto text = iter->get_string();

		iter += 1;

		return Identifier { location };
	}

	void Identifier::print_tree(u32 depth) const
	{
		std::cout << tree_branch(depth) << _location.get_string() << '\n';
}
}