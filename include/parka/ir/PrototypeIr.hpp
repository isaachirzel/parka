#ifndef PARKA_IR_PROTOTYPE_HPP
#define PARKA_IR_PROTOTYPE_HPP

#include "parka/ir/ParameterIr.hpp"
#include "parka/util/Array.hpp"

namespace parka::ir
{
	class PrototypeIr
	{
		Array<ParameterIr*> _parameters;
		TypeIr _returnType;

	public:

		PrototypeIr(Array<ParameterIr*>&& parameters, TypeIr&& returnType):
			_parameters(std::move(parameters)),
			_returnType(std::move(returnType))
		{}
		PrototypeIr(PrototypeIr&&) = default;
		PrototypeIr(const PrototypeIr&) = delete;

		void setReturnType(TypeIr&& type) { _returnType = std::move(type); }

		const auto& parameters() const { return _parameters; }
		const auto& returnType() const { return _returnType; }
	};
}

#endif
