#ifndef WARBLER_SEMANTICS_FUNCTION_SIGNATURE_HPP
#define WARBLER_SEMANTICS_FUNCTION_SIGNATURE_HPP

#include <warbler/syntax/function/function_signature.hpp>
#include <warbler/semantics/type/type.hpp>
#include <warbler/semantics/function/parameter.hpp>
#include <warbler/util/optional.hpp>

namespace warbler::semantics
{
	class FunctionSignature
	{
		Array<Parameter> _parameters;
		Optional<Type> _return_type;

	public:

		static Result<FunctionSignature> validate(const syntax::FunctionSignature& syntax);
	};
}

#endif
