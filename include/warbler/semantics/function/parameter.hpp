#ifndef WARBLER_SEMANTICS_PARAMETER_HPP
#define WARBLER_SEMANTICS_PARAMETER_HPP

#include <warbler/semantics/type/type.hpp>

namespace warbler::semantics
{
	enum class ParameterState
	{
		Valid,
		Invalid
	};

	class Parameter
	{
		Type _type;
		ParameterState _state;
		bool _is_mutable;

	public:

		Parameter(Type&& type, ParameterState state);
	};
}

#endif
