#include <warbler/ast/expression/prefix.hpp>

// local headers
#include <warbler/print.hpp>

// standard headers
#include <cstdlib>
#include <cassert>

namespace warbler
{

	Prefix::Prefix(PrefixType type) :
	_type(type)
	{}

	std::vector<Prefix> Prefix::parse_list(TokenIterator& iter)
	{
		std::vector<Prefix> out;

	parse_prefix:

		switch (iter->type())
		{
			case TOKEN_AMPERSAND:
				iter += 1;
				out.emplace_back(Prefix { PREFIX_REFERENCE });
				goto parse_prefix;

			case TOKEN_ASTERISK:
				iter += 1;
				out.emplace_back(Prefix { PREFIX_DEREFERENCE });
				goto parse_prefix;

			default:
				break;
		}

		return out;
	}

	void Prefix::print_tree(u32 depth) const
	{
		std::cout << tree_branch(depth);

		if (_type == PREFIX_REFERENCE)
		{
			std::cout << "&\n";
		}
		else
		{
			std::cout << "*\n";
		}
	}
}
