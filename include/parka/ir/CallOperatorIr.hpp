#ifndef PARKA_IR_CALL_OPERATOR_IR_HPP
#define PARKA_IR_CALL_OPERATOR_IR_HPP

#include "parka/ir/PrototypeIr.hpp"
#include "parka/ir/FunctionBodyIr.hpp"
#include "parka/util/Optional.hpp"

namespace parka::ir
{
	class CallOperatorIr
	{
		PrototypeIr _prototype;
		Optional<FunctionBodyIr> _body;
		bool _isIntrinsic;

	public:

		CallOperatorIr(PrototypeIr&& prototype):
			_prototype(std::move(prototype)),
			_body(),
			_isIntrinsic(true)
		{}
		CallOperatorIr(PrototypeIr&& prototype, Optional<FunctionBodyIr>&& body):
			_prototype(std::move(prototype)),
			_body(std::move(body)),
			_isIntrinsic(false)
		{}
		CallOperatorIr(CallOperatorIr&&) = default;
		CallOperatorIr(const CallOperatorIr&) = delete;

		void setBody(FunctionBodyIr&& body)
		{
			assert(!_isIntrinsic);

			_body = std::move(body);
		}

		const auto& prototype() const { return _prototype; }
		bool hasBody() const { return _body; }
		const auto& body() const { assert(_body); return *_body; }
		const auto& isIntrinsic() const { return _isIntrinsic; }
	};
}

#endif
