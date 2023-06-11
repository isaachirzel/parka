#include "parka/context/PackageContext.hpp"

namespace parka
{
	PackageContext::PackageContext(Array<PackageContext*> packages, Array<FunctionContext*>&& functions, Array<StructContext*>&& structs) :
	_packages(std::move(packages)),
	_functions(std::move(functions)),
	_structs(std::move(structs))
	{}
}
