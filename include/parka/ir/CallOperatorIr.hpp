#ifndef PARKA_IR_CALL_OPERATOR_IR_HPP
#define PARKA_IR_CALL_OPERATOR_IR_HPP

#include "parka/ir/TypeIr.hpp"
#include "parka/util/Array.hpp"
namespace parka::ir
{
	class CallOperatorIr
	{
		const TypeIr& _returnType;
		Array<TypeIr*> _parameterTypes;

	public:

		CallOperatorIr(const TypeIr& returnType, Array<TypeIr*>&& parameterTypes):
			_returnType(returnType),
			_parameterTypes(std::move(parameterTypes))
		{}
		CallOperatorIr(CallOperatorIr&&) = default;
		CallOperatorIr(const CallOperatorIr&) = delete;

		const auto& returnType() const { return _returnType; }
		const auto& parameterTypes() const { return _parameterTypes; }
	};
}

#endif
