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

		source::Location _location;

	public:

		Label(const source::Location& location);

		static Result<Label> parse(lexicon::TokenIterator& iter);

		void print_tree(u32 depth = 0) const;
	};
}

#endif
