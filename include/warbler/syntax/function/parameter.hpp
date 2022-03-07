#ifndef WARBLER_SYNTAX_FUNCTION_PARAMETER_HPP
#define WARBLER_SYNTAX_FUNCTION_PARAMETER_HPP

#include <warbler/syntax/identifier.hpp>
#include <warbler/syntax/type.hpp>

namespace warbler::syntax
{
	class Parameter
	{
	private:

		bool _is_mutable;
		Identifier _identifier;
		Type _type;

		Parameter(bool is_mutable, Identifier&& identifier, Type&& type);

	public:

		static Result<Parameter> parse(lexicon::Token& token);
		static Result<Array<Parameter>> parse_list(lexicon::Token& token);
	};
}

#endif
