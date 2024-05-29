#ifndef PARKA_IR_CALL_OPERATOR_IR_HPP
#define PARKA_IR_CALL_OPERATOR_IR_HPP

#include "parka/ir/FunctionBodyIr.hpp"
#include "parka/ir/ParameterIr.hpp"
#include "parka/ir/TypeIr.hpp"
#include "parka/util/Array.hpp"
#include "parka/util/Optional.hpp"

namespace parka::ir
{
	class CallOperatorIr
	{
		const TypeIr& _returnType;
		Array<ParameterIr*> _parameters;
		Optional<FunctionBodyIr> _body;
		bool _isIntrinsic;

	public:

		CallOperatorIr(const TypeIr& returnType, Array<ParameterIr*>&& parameterTypes):
			_returnType(returnType),
			_parameters(std::move(parameterTypes)),
			_body(),
			_isIntrinsic(true)
		{}
		CallOperatorIr(const TypeIr& returnType, Array<ParameterIr*>&& parameterTypes, Optional<FunctionBodyIr>&& body):
			_returnType(returnType),
			_parameters(std::move(parameterTypes)),
			_body(std::move(body)),
			_isIntrinsic(false)
		{}
		CallOperatorIr(CallOperatorIr&&) = default;
		CallOperatorIr(const CallOperatorIr&) = delete;

		const auto& returnType() const { return _returnType; }
		const auto& parameterTypes() const { return _parameters; }
		bool hasBody() const { return _body; }
		const auto& body() const { assert(_body); return *_body; }
		const auto& isIntrinsic() const { return _isIntrinsic; }
	};
}

#endif
