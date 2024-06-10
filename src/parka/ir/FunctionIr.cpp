#include "parka/ir/FunctionIr.hpp"
#include "parka/enum/IntrinsicFunctionType.hpp"
#include "parka/ir/FunctionBodyIr.hpp"
#include "parka/ir/PrimitiveIr.hpp"
#include "parka/ir/PrototypeIr.hpp"

namespace parka::ir
{
	FunctionIr FunctionIr::printlnFunction = intrinsic(IntrinsicFunctionType::Println, {}, PrimitiveIr::voidPrimitive);

	FunctionIr::FunctionIr(String symbol, PrototypeIr&& prototype, FunctionBodyIr&& body):
		EntityIr(EntityType::Function),
		_symbol(std::move(symbol)),
		_prototype(std::move(prototype)),
		_body(std::move(body))
	{}

	FunctionIr FunctionIr::intrinsic(IntrinsicFunctionType intrinsicFunctionType, Array<ParameterIr> parameters, const TypeIr& returnType)
	{
		auto symbol = symbolFromIntrinsicFunctionType(intrinsicFunctionType);
		auto parameterPtrs = Array<ParameterIr*>(parameters.length());

		for (usize i = 0; i < parameters.length(); ++i)
			parameterPtrs.push(new ParameterIr(std::move(parameters[i])));

		return FunctionIr(std::move(symbol), PrototypeIr(std::move(parameterPtrs), returnType), FunctionBodyIr(intrinsicFunctionType));
	}

	std::ostream& operator<<(std::ostream& out, const FunctionIr& function)
	{
		out << "function " << function._symbol;
		
		const auto& parameters = function._prototype.parameters();

		for (usize i = 0; i < parameters.length(); ++i)
		{
			if (i > 0)
				out << ", ";

			out << *parameters[i];
		}

		out << "): " << function._prototype.returnType();

		return out;
	}
}
