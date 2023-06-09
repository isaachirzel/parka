#include "parka/context/PrototypeContext.hpp"
#include "parka/log/Log.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/util/Array.hpp"

namespace parka
{
	PrototypeContext::PrototypeContext(Array<const ParameterContext*>&& parameters, ValueType&& returnType) :
	_parameters(std::move(parameters)),
	_returnType(std::move(returnType))
	{}

	static Optional<ValueType> validateReturnType(const Optional<TypeAnnotationSyntax>& syntax, SymbolTable& symbolTable)
	{
		if (!syntax)
			return ValueType::voidType;

		return ValueType::validate(*syntax, symbolTable);
	}

	Optional<PrototypeContext> PrototypeContext::validate(const PrototypeSyntax& syntax, FunctionSymbolTable& symbolTable)
	{
		auto success = true;
		const auto parameterCount = syntax.parameters().length();
		auto parameters = Array<const ParameterContext*>(parameterCount);

		for (const auto *parameterSyntax : syntax.parameters())
		{
			auto *parameterContext = ParameterContext::validate(*parameterSyntax, symbolTable);

			if (parameterContext == nullptr)
			{
				success = false;
				continue;
			}

			parameters.push(parameterContext);
		}

		auto returnType = validateReturnType(syntax.returnType(), symbolTable);

		if (!returnType)
			success = false;

		if (!success)
			return {};

		auto context = PrototypeContext(std::move(parameters), *returnType);

		return context;
	}
}