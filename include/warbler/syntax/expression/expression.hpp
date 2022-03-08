#ifndef WARBLER_SYNTAX_EXPRESSION_HPP
#define WARBLER_SYNTAX_EXPRESSION_HPP

#include <warbler/syntax/type.hpp>
#include <warbler/lexicon/token.hpp>
#include <warbler/semantics/symbol_table.hpp>
#include <warbler/util/ptr.hpp>
#include <warbler/util/result.hpp>

namespace warbler::syntax
{
	struct Expression
	{
		virtual ~Expression() = default;
		//virtual bool validate(semantics::SymbolTable& symbols) = 0;

		static Result<Ptr<Expression>> parse(lexicon::Token& token);
	};
}

#endif
