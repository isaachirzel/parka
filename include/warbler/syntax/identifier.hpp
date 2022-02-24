#ifndef WARBLER_SYNTAX_NAME_HPP
#define WARBLER_SYNTAX_NAME_HPP

#include <warbler/lexicon/token.hpp>
#include <warbler/util/result.hpp>
#include <warbler/util/string.hpp>

namespace warbler::syntax
{
	class Identifier
	{
	private:

		source::Location _location;

		Identifier(const source::Location& location);

	public:

		static Result<Identifier> parse(lexicon::TokenIterator& iter);

		void print_tree(u32 depth = 0) const;

		const source::Location& location() const { return _location; }
	};
}

#endif
