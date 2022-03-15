#ifndef WARBLER_SEMANTICS_PARAMETER_HPP
#define WARBLER_SEMANTICS_PARAMETER_HPP

#include <warbler/syntax/function/parameter.hpp>
#include <warbler/semantics/type/type.hpp>

namespace warbler::semantics
{
	class Parameter
	{
		String _symbol;
		Type _type;
		bool _is_valid;
		bool _is_mutable;

		Parameter(String&& symbol, Type&& type, bool _is_valid, bool is_mutable);

	public:

		static Result<Parameter> validate(const syntax::Parameter& syntax);
		const String& symbol() const { return _symbol; }
	};
}

#endif
