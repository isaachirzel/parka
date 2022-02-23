#ifndef WARBLER_SYNTAX_LABEL_HPP
#define WARBLER_SYNTAX_LABEL_HPP

// local headers
#include <warbler/lexicon/token.hpp>
#include <warbler/util/primitive.hpp>
#include <warbler/util/result.hpp>

namespace warbler::syntax
{
	class Label
	{
	private:

		String _identifier;

	public:

		Label(String&& identifier);

		static Result<Label> parse(TokenIterator& iter);

		void print_tree(u32 depth = 0) const;
	};
}

#endif
