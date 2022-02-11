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
		PREFIX_DEREFERENCE,
		PREFIX_POSITIVE,
		PREFIX_NEGATIVE,
		PREFIX_BITWISE_NOT,
		PREFIX_BOOLEAN_NOT
	};

	class Prefix
	{
	private:

		PrefixType _type;
		Location _location;

	public:

		Prefix(PrefixType type, const Location& location);

		static std::vector<Prefix> parse_list(TokenIterator& iter);

		void print_tree(u32 depth = 0) const;

		PrefixType type() const { return _type; }
		const Location& location() const { return _location; }
	};
}

#endif
