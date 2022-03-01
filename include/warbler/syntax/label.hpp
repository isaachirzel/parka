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

		lexicon::Token _token;

	public:

		Label(const lexicon::Token& token);

		static Result<Label> parse(lexicon::Token& token);

		void print_tree(u32 depth = 0) const;
	};
}

#endif
