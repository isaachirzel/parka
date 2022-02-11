#include <warbler/ast/expression/prefix.hpp>

// local headers
#include <warbler/print.hpp>

// standard headers
#include <cstdlib>
#include <cassert>

namespace warbler::ast
{

	Prefix::Prefix(PrefixType type, const Location& location) :
	_type(type),
	_location(location)
	{}

	std::vector<Prefix> Prefix::parse_list(TokenIterator& iter)
	{
		std::vector<Prefix> out;
		PrefixType type;

	parse_prefix:

		switch (iter->type())
		{
			case TOKEN_AMPERSAND:
				type = PREFIX_REFERENCE;
				break;

			case TOKEN_ASTERISK:
				type = PREFIX_DEREFERENCE;
				break;

			case TOKEN_PLUS:
				type = PREFIX_POSITIVE;
				break;

			case TOKEN_MINUS:
				type = PREFIX_NEGATIVE;
				break;

			case TOKEN_BITWISE_NOT:
				type = PREFIX_BITWISE_NOT;
				break;

			case TOKEN_BOOLEAN_NOT:
				type = PREFIX_BOOLEAN_NOT;
				break;

			default:
				goto finish;
		}
	
		iter += 1;
		out.emplace_back(Prefix { type, iter->location() });
		goto parse_prefix;

	finish:

		return out;
	}

	void Prefix::print_tree(u32 depth) const
	{
		std::cout << tree_branch(depth);

		switch (_type)
		{
			case PREFIX_REFERENCE:
				std::cout << "&\n";
				break;

			case PREFIX_DEREFERENCE:
				std::cout << "*\n";
				break;

			case PREFIX_POSITIVE:
				std::cout << "+\n";
				break;

			case PREFIX_NEGATIVE:
				std::cout << "-\n";
				break;

			case PREFIX_BITWISE_NOT:
				std::cout << "~\n";
				break;

			case PREFIX_BOOLEAN_NOT:
				std::cout << "!\n";
				break;
		}
	}
}
