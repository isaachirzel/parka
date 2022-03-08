#ifndef WARBLER_SYNTAX_IDENTIFIER_HPP
#define WARBLER_SYNTAX_IDENTIFIER_HPP

// local headers
#include <warbler/lexicon/token.hpp>
#include <warbler/util/result.hpp>
#include <warbler/util/primitive.hpp>
#include <warbler/syntax/expression/expression.hpp>
#include <warbler/semantics/context.hpp>

namespace warbler::syntax
{
	class Symbol : public Expression
	{
	private:

		lexicon::Token _token;

	public:

		Symbol(const lexicon::Token& token);

		static Result<Symbol> parse(lexicon::Token& token);

		bool validate(semantics::Context& context);
		void print_tree(u32 depth = 0) const;
	};

}
#endif
