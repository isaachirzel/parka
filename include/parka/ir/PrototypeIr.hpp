#ifndef PARKA_IR_PROTOTYPE_IR_HPP
#define PARKA_IR_PROTOTYPE_IR_HPP

#include "parka/ir/CallOperatorIr.hpp"
#include "parka/ir/ParameterIr.hpp"
#include "parka/ir/TypeIr.hpp"
#include "parka/util/Array.hpp"

namespace parka::ir
{
	class PrototypeIr: public TypeIr
	{
		Array<ParameterIr*> _parameters;
		const TypeIr& _returnType;

	public:

		PrototypeIr(Array<ParameterIr*>&& parameters, const TypeIr& returnType);
		PrototypeIr(PrototypeIr&&) = default;
		PrototypeIr(const PrototypeIr&) = delete;

		std::ostream& printType(std::ostream& out) const;

		const auto& parameters() const { return _parameters; }
		const auto& returnType() const { return _returnType; }

		bool operator==(const TypeIr& other) const;
		bool operator!=(const TypeIr& other) const;
	};
}

#endif
