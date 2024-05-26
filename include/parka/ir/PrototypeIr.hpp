#ifndef PARKA_IR_PROTOTYPE_IR_HPP
#define PARKA_IR_PROTOTYPE_IR_HPP

#include "parka/ir/ParameterIr.hpp"
#include "parka/util/Array.hpp"

namespace parka::ir
{
	class PrototypeIr
	{
		Array<ParameterIr*> _parameters;
		const TypeIr* _returnType;

	public:

		PrototypeIr(Array<ParameterIr*>&& parameters, const TypeIr& returnType):
			_parameters(std::move(parameters)),
			_returnType(&returnType)
		{}
		PrototypeIr(PrototypeIr&&) = default;
		PrototypeIr(const PrototypeIr&) = delete;

		void setReturnType(const TypeIr& type) { _returnType = &type; }

		const auto& parameters() const { return _parameters; }
		const auto& returnType() const { return *_returnType; }
	};
}

#endif
