#include "parka/ir/Struct.hpp"
#include "parka/log/Log.hpp"

namespace parka::ir
{
	const ValueType *StructIr::valueType() const
	{
		log::error("Unable to get value of struct `$`.", _symbol);

		return nullptr;
	}
}