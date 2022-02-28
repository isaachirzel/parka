#include <warbler/syntax/label.hpp>

// local headers
#include <warbler/util/print.hpp>

namespace warbler::syntax
{
	Label::Label(const source::Location& location) :
	_location(location)
	{}

	Result<Label> Label::parse(lexicon::TokenIterator& iter)
	{

		if (iter->type() != lexicon::TokenType::Identifier)
		{
			print_parse_error(iter, "label identifer");
			return {};
		}

		const auto& location = iter->location();

		iter += 1;

		if (iter->type() != lexicon::TokenType::Colon)
		{
			print_parse_error(iter, "':' after label");
			return {};
		}

		iter += 1;

		return Label(location);
	}

	void Label::print_tree(u32 depth) const
	{
		print_branch(depth, _location.text());
	}
}
