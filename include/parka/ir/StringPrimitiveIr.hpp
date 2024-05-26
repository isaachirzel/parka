#ifndef PARKA_IR_STRING_PRIMITIVE_IR_HPP
#define PARKA_IR_STRING_PRIMITIVE_IR_HPP

#include "parka/ir/LValueIr.hpp"
#include "parka/ir/TypeBaseIr.hpp"

namespace parka::ir
{
	class StringPrimitiveIr: public TypeBaseIr, public LValueIr
	{
		String _name;

	public:

		static StringPrimitiveIr stringPrimitive;

	private:

		StringPrimitiveIr(const char *name);
		StringPrimitiveIr(StringPrimitiveIr&&) = default;
		StringPrimitiveIr(const StringPrimitiveIr&) = delete;

	public:

		const TypeIr& type() const { return TypeIr::typeNameType; }
		const String& symbol() const { return _name; }
	};
}

#endif
