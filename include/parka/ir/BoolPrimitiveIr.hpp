#ifndef PARKA_IR_BOOL_PRIMITIVE_IR_HPP
#define PARKA_IR_BOOL_PRIMITIVE_IR_HPP

#include "parka/ir/LValueIr.hpp"
#include "parka/ir/TypeBaseIr.hpp"

namespace parka::ir
{
	class BoolPrimitiveIr: public TypeBaseIr, public LValueIr
	{
		String _name;

	public:

		static BoolPrimitiveIr boolPrimitive;

	private:

		BoolPrimitiveIr(const char *name);
		BoolPrimitiveIr(BoolPrimitiveIr&&) = default;
		BoolPrimitiveIr(const BoolPrimitiveIr&) = delete;

	public:

		const TypeIr& type() const { return TypeIr::typeNameType; }
		const String& symbol() const { return _name; }
	};
}

#endif
