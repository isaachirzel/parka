#ifndef PARKA_ENUM_DECLARABLE_TYPE_HPP
#define PARKA_ENUM_DECLARABLE_TYPE_HPP

namespace parka
{
	enum class DeclarableType
	{
		Struct,
		Function,
		Variable,
		Parameter,
		Member
	};

	std::ostream& operator<<(std::ostream& out, const DeclarableType& declarableType);
}

#endif
