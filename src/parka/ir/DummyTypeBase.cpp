#include "parka/ir/DummyTypeBase.hpp"

namespace parka::ir
{
	DummyTypeBase const DummyTypeBase::packageTypeBase("package");
	DummyTypeBase const DummyTypeBase::typeNameTypeBase("type name");
	// TODO: This should actually refer to the type of the function
	DummyTypeBase const DummyTypeBase::functionTypeBase("function");
	DummyTypeBase const DummyTypeBase::integerTypeBase("integer");
	DummyTypeBase const DummyTypeBase::floatTypeBase("float");

	DummyTypeBase::DummyTypeBase(const char *name):
		_symbol(name)
	{}
}
