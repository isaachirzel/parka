#ifndef WARBLER_SEMANTICS_VARIABLE_HPP
#define WARBLER_SEMANTICS_VARIABLE_HPP

#include <warbler/util/string.hpp>
#include <warbler/util/optional.hpp>
#include <warbler/semantics/type/type.hpp>

namespace warbler::semantics
{
	enum class VariableState
	{
		Declared,
		Defined,
		Invalid
	};

	class Variable
	{
		String _name;
		Optional<Type> _type;
		VariableState _state;
		bool _is_mutable;

	public:

		Variable(String&& name, Type&& type, bool is_mutable);

		const String& name() const { return _name; }
	};
}

#endif