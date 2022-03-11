#ifndef WARBLER_SEMANTICS_TYPE_HPP
#define WARBLER_SEMANTICS_TYPE_HPP

#include <warbler/util/array.hpp>
//#include <warbler/semantics/type/definition.hpp>

namespace warbler::semantics
{
	class Definition;
	
	class Type
	{
		Array<bool> _ptr_mutability;
		Definition& base_type;

	public:

		Type(const Array<bool>& ptr_info, Definition& base_type);
	};
}

#endif
