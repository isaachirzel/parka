#ifndef PARKA_IR_F64_PRIMITIVE_IR_HPP
#define PARKA_IR_F64_PRIMITIVE_IR_HPP

#include "parka/ir/EntityIr.hpp"
#include "parka/ir/InvalidTypeIr.hpp"

namespace parka::ir
{
	class F64PrimitiveIr: public TypeIr, public EntityIr
	{
		String _symbol;

	public:

		static F64PrimitiveIr instance;

	private:

		F64PrimitiveIr();
		F64PrimitiveIr(F64PrimitiveIr&&) = delete;
		F64PrimitiveIr(const F64PrimitiveIr&) = delete;

	public:

		std::ostream& printType(std::ostream& out) const;
		const String& symbol() const { return _symbol; }
		const TypeIr& type() const { return InvalidTypeIr::typeNameType; }
	};
}

#endif
