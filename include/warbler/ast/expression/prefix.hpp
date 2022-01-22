#ifndef WARBLER_AST_EXPRESSION_PREFIX_HPP
#define WARBLER_AST_EXPRESSION_PREFIX_HPP

// local headers
#include <warbler/token.hpp>
#include <warbler/util/result.hpp>

namespace warbler::ast
{
	enum PrefixType
	{
		PREFIX_REFERENCE,
		PREFIX_DEREFERENCE
	};

	class Prefix
	{
	private:

		PrefixType _type;

	public:

		Prefix(PrefixType type);

		static std::vector<Prefix> parse_list(TokenIterator& iter);

		void print_tree(u32 depth = 0) const;
	};
}

#endif
