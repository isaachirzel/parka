#ifndef WARBLER_SYNTAX_FUNCTION_FUNCTION_SIGNATURE_HPP
#define WARBLER_SYNTAX_FUNCTION_FUNCTION_SIGNATURE_HPP

#include <warbler/syntax/function/parameter.hpp>
#include <warbler/util/optional.hpp>
#include <warbler/syntax/type.hpp>

namespace warbler::syntax
{
	class FunctionSignature
	{
	private:

		Array<Parameter> _parameters;
		Optional<Type> _return_type;

		FunctionSignature(Array<Parameter>&& parameters, Optional<Type>&& return_type);

	public:

		static Result<FunctionSignature> parse(lexicon::Token& token);
	};
}

#endif
