#ifndef PARKA_IR_CALL_OPERATOR_IR_HPP
#define PARKA_IR_CALL_OPERATOR_IR_HPP

#include "parka/ir/PrototypeIr.hpp"
#include "parka/ir/FunctionBodyIr.hpp"
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

		CallOperatorIr(const PrototypeIr& prototype):
			_prototype(prototype),
			_body(),
			_isIntrinsic(true)
		{}
		CallOperatorIr(const PrototypeIr& prototype, Optional<FunctionBodyIr>&& body):
			_prototype(prototype),
			_body(std::move(body)),
			_isIntrinsic(false)
		{}
		CallOperatorIr(CallOperatorIr&&) = default;
		CallOperatorIr(const CallOperatorIr&) = delete;

		const auto& prototype() const { return _prototype; }
		bool hasBody() const { return _body; }
		const auto& body() const { assert(_body); return *_body; }
		const auto& isIntrinsic() const { return _isIntrinsic; }
	};
}

#endif
