#ifndef PARKA_VALIDATION_INTRINSIC_ENTRY_HPP
#define PARKA_VALIDATION_INTRINSIC_ENTRY_HPP

#include "parka/ir/EntityIr.hpp"
#include "parka/validation/ContextEntry.hpp"
namespace parka::validation
{
	class IntrinsicEntry: public ContextEntry
	{
		ir::EntityIr& _ir;

	public:

		IntrinsicEntry(ir::EntityIr& ir):
			ContextEntry(ir.resolvableType),
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
