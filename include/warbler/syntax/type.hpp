#ifndef WARBLER_SYNTAX_TYPE_HPP
#define WARBLER_SYNTAX_TYPE_HPP

// local headers
#include <cassert>
#include <warbler/lexicon/token.hpp>
#include <warbler/util/result.hpp>
#include <warbler/util/primitive.hpp>
#include <warbler/syntax/type/type_definition.hpp>
#include <warbler/semantics/context.hpp>

namespace warbler::syntax
{
	class Type
	{
		struct PtrToken
		{
			lexicon::Token token;
			bool is_mutable;
		};

		lexicon::Token _base_type;
		Array<PtrToken> _ptrs;

		Type(const lexicon::Token& base_type, Array<PtrToken>&& ptrs);

	public:

		static Result<Type> parse(lexicon::Token& token);
		bool validate(semantics::Context& context);
	};
}

#endif
