#ifndef WARBLER_AST_EXPRESSION_PREFIX_HPP
#define WARBLER_AST_EXPRESSION_PREFIX_HPP

// local headers
#include <warbler/token.hpp>
#include <warbler/result.hpp>

namespace warbler
{
	enum PrefixType
	{
		PREFIX_INCREMENT,
		PREFIX_DECREMENT,
		PREFIX_REFERENCE,
		PREFIX_DEREFERENCE
	};

	class Prefix
	{
	private:

		PrefixType _type;

	public:

		Prefix(PrefixType type);

		static Result<Prefix> parse(TokenIterator& iter);
		static Result<std::vector<Prefix>> parse_list(TokenIterator& iter);

		void print_tree(u32 depth = 0) const;
	};
}

#endif
