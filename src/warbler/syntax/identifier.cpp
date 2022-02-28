#include <warbler/syntax/identifier.hpp>

#include <warbler/util/print.hpp>

namespace warbler::syntax
{
	using source::Location;
	using lexicon::TokenIterator;

	Identifier::Identifier(const source::Location& location) :
	_location(location)
	{}

	Result<Identifier> Identifier::parse(lexicon::TokenIterator& iter)
	{
		if (iter->type() != lexicon::TokenType::Identifier)
			return {};

		const auto& location = iter->location();
		auto text = iter->get_string();

		iter += 1;

		return Identifier { location };
	}

	void Identifier::print_tree(u32 depth) const
	{
		print_branch(depth, _location.text());
	}
}