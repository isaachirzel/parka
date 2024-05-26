#ifndef PARKA_IR_VOID_PRIMITIVE_IR_HPP
#define PARKA_IR_VOID_PRIMITIVE_IR_HPP

#include "parka/ir/LValueIr.hpp"
#include "parka/ir/TypeBaseIr.hpp"

namespace parka::ir
{
	class VoidPrimitiveIr: public TypeBaseIr, public LValueIr
	{
		String _name;

	public:

		static VoidPrimitiveIr voidPrimitive;

	private:

		VoidPrimitiveIr(const char *name);
		VoidPrimitiveIr(VoidPrimitiveIr&&) = default;
		VoidPrimitiveIr(const VoidPrimitiveIr&) = delete;

	public:

		const TypeIr& type() const { return TypeIr::typeNameType; }
		const String& symbol() const { return _name; }
	};
}

#endif
