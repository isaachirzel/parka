#ifndef PARKA_CONTEXT_PROTOTYPE_CONTEXT_HPP
#define PARKA_CONTEXT_PROTOTYPE_CONTEXT_HPP

#include "parka/context/ParameterContext.hpp"
#include "parka/symbol/FunctionSymbolTable.hpp"
#include "parka/util/Optional.hpp"
namespace parka
{
	class PrototypeContext
	{
		Array<const ParameterContext*> _parameters;
		ValueType _returnType;

	private:

		PrototypeContext(Array<const ParameterContext*>&& parameters, ValueType&& returnType);

	public:

		PrototypeContext(PrototypeContext&&) = default;
		PrototypeContext(const PrototypeContext&) = delete;

		static Optional<PrototypeContext> validate(const PrototypeSyntax& syntax, FunctionSymbolTable& symbolTable);
	};
}

#endif
