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

	static Result<Prefix> parse(TokenIterator& iter)
	{
		switch (iter->type())
		{
			case TOKEN_INCREMENT:
				iter += 1;
				return Prefix(PREFIX_INCREMENT);

			case TOKEN_DECREMENT:
				iter += 1;
				return Prefix(PREFIX_DECREMENT);

			case TOKEN_AMPERSAND:
				iter += 1;
				return Prefix(PREFIX_REFERENCE);

			case TOKEN_ASTERISK:
				iter += 1;
				return Prefix(PREFIX_DEREFERENCE);

			default:
				return ERROR_NOT_FOUND;
		}
	}

	static Result<std::vector<Prefix>> parse_list(TokenIterator& iter)
	{
		std::vector<Prefix> out;

		while (true)
		{
			auto res = Prefix::parse(iter);

			if (res.has_error())
				break;
			
			out.emplace_back(res.unwrap());
		}

		return out;
	}

	void Prefix::print_tree(u32 depth) const
	{
		print_branch(depth);

		switch (_type)
		{
			case PREFIX_INCREMENT:
				puts("++");
				break;

			case PREFIX_DECREMENT:
				puts("--");
				break;

			case PREFIX_REFERENCE:
				puts("&");
				break;

			case PREFIX_DEREFERENCE:
				puts("*");
				break;
		}
	}
}
