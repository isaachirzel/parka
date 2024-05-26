#ifndef PARKA_IR_CHAR_PRIMITIVE_IR_HPP
#define PARKA_IR_CHAR_PRIMITIVE_IR_HPP

#include "parka/ir/LValueIr.hpp"
#include "parka/ir/TypeBaseIr.hpp"

namespace parka::ir
{
	class CharPrimitiveIr: public TypeBaseIr, public LValueIr
	{
		String _name;

	public:

		static CharPrimitiveIr charPrimitive;

	private:

		CharPrimitiveIr(const char *name);
		CharPrimitiveIr(CharPrimitiveIr&&) = default;
		CharPrimitiveIr(const CharPrimitiveIr&) = delete;

	public:

		const TypeIr& type() const { return TypeIr::typeNameType; }
		const String& symbol() const { return _name; }
	};
}

#endif
