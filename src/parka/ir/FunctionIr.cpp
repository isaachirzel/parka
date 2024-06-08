#include "parka/ir/FunctionIr.hpp"
#include "parka/enum/IntrinsicFunctionType.hpp"
#include "parka/ir/PrimitiveIr.hpp"
#include "parka/ir/PrototypeIr.hpp"

namespace parka::ir
{
	FunctionIr FunctionIr::printFunction("print", PrototypeIr({}, PrimitiveIr::voidPrimitive), IntrinsicFunctionType::Print);

	FunctionIr::FunctionIr(String symbol, PrototypeIr&& prototype, FunctionBodyIr&& body):
		EntityIr(EntityType::Function),
		_symbol(std::move(symbol)),
		_prototype(std::move(prototype)),
		_body(std::move(body))
	{}

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
