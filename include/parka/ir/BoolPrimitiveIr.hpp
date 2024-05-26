#ifndef PARKA_IR_BOOL_PRIMITIVE_IR_HPP
#define PARKA_IR_BOOL_PRIMITIVE_IR_HPP

#include "parka/ir/LValueIr.hpp"
#include "parka/ir/TypeIr.hpp"
#include "parka/ir/TypeNameIr.hpp"

namespace parka::ir
{
	class BoolPrimitiveIr: public TypeIr, public LValueIr
	{
		String _name;

	public:

		static BoolPrimitiveIr boolPrimitive;

	private:

		BoolPrimitiveIr(const char *name);
		BoolPrimitiveIr(BoolPrimitiveIr&&) = default;
		BoolPrimitiveIr(const BoolPrimitiveIr&) = delete;

	public:

		std::ostream& printType(std::ostream& out) const;

		const TypeIr& type() const { return TypeNameIr::typeNameType; }
		const String& symbol() const { return _name; }
	};
}

#endif
