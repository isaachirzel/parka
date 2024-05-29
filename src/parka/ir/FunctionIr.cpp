#include "parka/ir/FunctionIr.hpp"
#include "parka/ir/VoidPrimitiveIr.hpp"

namespace parka::ir
{
	FunctionIr FunctionIr::printFunction("print", PrototypeIr({}, VoidPrimitiveIr::instance));

	CallOperatorIr* FunctionIr::getCallOperator(const Array<ExpressionIr*>& arguments) const
	{
		auto argumentCount = arguments.length();

		if (argumentCount != _prototype.parameters().length())
			return nullptr;

		for (usize i = 0; i < argumentCount; ++i)
		{
			auto& argument = *arguments[i];
			auto& parameter = *_prototype.parameters()[i];
			auto* conversion = argument.type().getConversion(parameter.type());

			if (!conversion)
				return nullptr;
		}

		return nullptr;
	}

	std::ostream& FunctionIr::printType(std::ostream& out) const
	{
		out << "function (";
		bool isFirst = true;

		for (const auto* parameter : _prototype.parameters())
		{
			if (!isFirst)
				out << ", ";

			out << parameter->type();
			isFirst = false;
		}

		out << "): " << _prototype.returnType();

		return out;
	}

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
}
