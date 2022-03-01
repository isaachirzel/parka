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

		lexicon::Token _token;

		Identifier(const lexicon::Token& token);

	public:

		static Result<Identifier> parse(lexicon::Token& token);

		void print_tree(u32 depth = 0) const;

		const lexicon::Token& token() const { return _token; }
	};
}

#endif
