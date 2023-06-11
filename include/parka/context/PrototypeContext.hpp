#ifndef PARKA_CONTEXT_PROTOTYPE_CONTEXT_HPP
#define PARKA_CONTEXT_PROTOTYPE_CONTEXT_HPP

#include "parka/context/ParameterContext.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	class PrototypeContext
	{
		Array<ParameterContext*> _parameters;
		ValueType _returnType;

	public:

		PrototypeContext(Array<ParameterContext*>&& parameters, ValueType&& returnType) :
		_parameters(std::move(parameters)),
		_returnType(std::move(returnType))
		{}
		PrototypeContext(PrototypeContext&&) = default;
		PrototypeContext(const PrototypeContext&) = delete;

		const auto& parameters() const { return _parameters; }
		const auto& returnType() const { return _returnType; }
	};
}

#endif
