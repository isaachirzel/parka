#ifndef WARBLER_SEMANTICS_TYPE_INFO_HPP
#define WARBLER_SEMANTICS_TYPE_INFO_HPP

namespace warbler::semantics
{
	/*
		class that'll store all of the data invololved in the 
		comparison of symbols

	*/

	enum class BaseType
	{
		Struct,
		Function,
		Primitive,
		Auto
	};

	struct Type
	{
		BaseType type();
		bool can_cast_from(const Type& other);
	};
}

#endif
