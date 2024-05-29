#ifndef PARKA_IR_CALL_OPERATOR_IR_HPP
#define PARKA_IR_CALL_OPERATOR_IR_HPP

#include "parka/ir/FunctionBodyIr.hpp"
#include "parka/ir/TypeIr.hpp"
#include "parka/util/Optional.hpp"

namespace parka::ir
{
	class PrototypeIr;

	class CallOperatorIr
	{
		const PrototypeIr& _prototype;
		Optional<FunctionBodyIr> _body;
		bool _isIntrinsic;

	public:

		CallOperatorIr():
			_body(),
			_isIntrinsic(true)
		{}
		CallOperatorIr(const PrototypeIr&Optional<FunctionBodyIr>&& body):
			_body(std::move(body)),
			_isIntrinsic(false)
		{}
		CallOperatorIr(CallOperatorIr&&) = default;
		CallOperatorIr(const CallOperatorIr&) = delete;

		bool hasBody() const { return _body; }
		const auto& body() const { assert(_body); return *_body; }
		const auto& isIntrinsic() const { return _isIntrinsic; }
	};
}

#endif
