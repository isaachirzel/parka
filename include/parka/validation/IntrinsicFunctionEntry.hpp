#ifndef PARKA_INTRINSIC_FUNCTION_ENTRY_HPP
#define PARKA_INTRINSIC_FUNCTION_ENTRY_HPP

#include "parka/ir/IntrinsicFunctionIr.hpp"
#include "parka/validation/Resolvable.hpp"

namespace parka::validation
{
	class IntrinsicFunctionEntry: public Resolvable
	{
		ir::IntrinsicFunctionIr& _ir;

	public:

		IntrinsicFunctionEntry(ir::IntrinsicFunctionIr& ir):
			Resolvable(ResolvableType::IntrinsicFunction),
			_ir(ir)
		{}
		IntrinsicFunctionEntry(IntrinsicFunctionEntry&&) = default;
		IntrinsicFunctionEntry(const IntrinsicFunctionEntry&) = delete;

		Context* context() { return nullptr; }
		const String& name() const { return _ir.symbol(); }
		ir::IntrinsicFunctionIr* resolve() { return &_ir; }
	};
}

#endif
