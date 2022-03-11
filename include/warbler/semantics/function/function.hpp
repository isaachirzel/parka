#ifndef WARBLER_SEMANTICS_FUNCTION_HPP
#define WARBLER_SEMANTICS_FUNCTION_HPP

#include <warbler/semantics/function/parameter.hpp>
#include <warbler/util/optional.hpp>

namespace warbler::semantics
{
	class Function
	{
		String _name;
		Array<Parameter> _parameters;
		Optional<Type> _return_type;

	public:

		Function(Array<Parameter>&& parameters, Optional<Type>&& type);
	};
}

#endif
