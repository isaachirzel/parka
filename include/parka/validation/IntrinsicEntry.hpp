#ifndef PARKA_VALIDATION_INTRINSIC_ENTRY_HPP
#define PARKA_VALIDATION_INTRINSIC_ENTRY_HPP

#include "parka/ir/EntityIr.hpp"
#include "parka/validation/Resolvable.hpp"
namespace parka::validation
{
	class IntrinsicEntry: public Resolvable
	{
		ir::EntityIr& _ir;

	public:

		IntrinsicEntry(ir::EntityIr& ir):
			Resolvable(ir.resolvableType),
			_ir(ir)
		{}
		IntrinsicEntry(IntrinsicEntry&&) = default;
		IntrinsicEntry(const IntrinsicEntry&) = delete;

		Context* context() { return nullptr; }
		const String& name() const { return _ir.symbol(); }
		ir::EntityIr* resolve() { return &_ir; }
	};
}

#endif
