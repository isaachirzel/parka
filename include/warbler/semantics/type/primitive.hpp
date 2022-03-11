#ifndef WARBLER_SEMANTICS_PRIMITIVE_HPP
#define WARBLER_SEMANTICS_PRIMITIVE_HPP

#include <warbler/semantics/type/definition.hpp>

namespace warbler::semantics
{
	class Primitive
	{
		Definition& definition;
	
	public:

		Primitive(Definition& definition);
	};
}

#endif