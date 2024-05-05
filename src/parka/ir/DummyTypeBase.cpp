#include "parka/ir/DummyTypeBase.hpp"

namespace parka::ir
{
	DummyTypeBase DummyTypeBase::packageTypeBase("package");
	DummyTypeBase DummyTypeBase::typeNameTypeBase("type name");
	// TODO: This should actually refer to the type of the function
	DummyTypeBase DummyTypeBase::functionTypeBase("function");

	DummyTypeBase::DummyTypeBase(const char *name):
		_symbol(name)
	{}
}
