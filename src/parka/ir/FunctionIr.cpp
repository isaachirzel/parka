#include "parka/ir/FunctionIr.hpp"
#include "parka/ir/VoidPrimitiveIr.hpp"
#include "parka/log/Log.hpp"

namespace parka::ir
{
	FunctionIr FunctionIr::printFunction("print", PrototypeIr({}, VoidPrimitiveIr::voidPrimitive));

	bool FunctionIr::operator==(const TypeIr& other) const
	{
		if (other.typeCategory != TypeCategory::Function)
			return false;

		auto& otherFunction = static_cast<const FunctionIr&>(other);
		auto& otherPrototype = otherFunction._prototype;

		if (_prototype.parameters().length() != otherPrototype.parameters().length())
			return false;

		usize parameterCount = _prototype.parameters().length();

		for (usize i = 0; i < parameterCount; ++i)
		{
			auto& a = *_prototype.parameters()[i];
			auto& b = *otherPrototype.parameters()[i];

			if (a.type() != b.type())
				return false;
		}

		return true;
	}

	bool FunctionIr::operator!=(const TypeIr& other) const
	{
		return !(*this == other);
	}

	std::ostream& FunctionIr::printType(std::ostream& out) const
	{
		

		return out;
	}
}
