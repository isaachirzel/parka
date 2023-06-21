#ifndef PARKA_ENUM_RESOLVABLE_TYPE_HPP
#define PARKA_ENUM_RESOLVABLE_TYPE_HPP

namespace parka
{
	enum class ResolvableType
	{
		Package,
		Primitive,
		Struct,
		Function,
		Variable,
		Parameter,
		Member
	};

	std::ostream& operator<<(std::ostream& out, const ResolvableType& type);
}

#endif
