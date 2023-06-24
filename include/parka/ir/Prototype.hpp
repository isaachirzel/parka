#ifndef PARKA_IR_PROTOTYPE_HPP
#define PARKA_IR_PROTOTYPE_HPP

#include "parka/ir/Parameter.hpp"
#include "parka/util/Array.hpp"

namespace parka::ir
{
	class PrototypeIr
	{
		Array<ParameterIr*> _parameters;
		ValueType _returnType;

	public:

		PrototypeIr(Array<ParameterIr*>&& parameters, ValueType&& returnType):
		_parameters(std::move(parameters)),
		_returnType(std::move(returnType))
		{}
		PrototypeIr(PrototypeIr&&) = default;
		PrototypeIr(const PrototypeIr&) = delete;

		const auto& parameters() const { return _parameters; }
		const auto& returnType() const { return _returnType; }
	};
}

#endif
