#include "parka/ir/Package.hpp"
#include "parka/log/Log.hpp"

namespace parka::ir
{
	const ValueType *PackageIr::valueType() const
	{
		log::error("Unable to get value of package `$`.", _symbol);
		return nullptr;
	}
}
