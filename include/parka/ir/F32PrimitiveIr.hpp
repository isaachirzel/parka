#ifndef PARKA_IR_F32_PRIMITIVE_IR_HPP
#define PARKA_IR_F32_PRIMITIVE_IR_HPP

#include "parka/ir/EntityIr.hpp"
#include "parka/ir/InvalidTypeIr.hpp"

namespace parka::ir
{
	class F32PrimitiveIr: public TypeIr, public EntityIr
	{
		String _symbol;

	public:

		static F32PrimitiveIr instance;

	private:

		F32PrimitiveIr();
		F32PrimitiveIr(F32PrimitiveIr&&) = delete;
		F32PrimitiveIr(const F32PrimitiveIr&) = delete;

	public:

		std::ostream& printType(std::ostream& out) const;
		const String& symbol() const { return _symbol; }
		const TypeIr& type() const { return InvalidTypeIr::typeNameType; }
	};
}

#endif
