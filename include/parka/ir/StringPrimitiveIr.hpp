#ifndef PARKA_IR_STRING_PRIMITIVE_IR_HPP
#define PARKA_IR_STRING_PRIMITIVE_IR_HPP

#include "parka/ir/LValueIr.hpp"
#include "parka/ir/TypeIr.hpp"
#include "parka/ir/TypeNameIr.hpp"

namespace parka::ir
{
	class StringPrimitiveIr: public TypeIr, public LValueIr
	{
		String _name;

	public:

		static StringPrimitiveIr stringPrimitive;

	private:

		StringPrimitiveIr(const char *name);
		StringPrimitiveIr(StringPrimitiveIr&&) = default;
		StringPrimitiveIr(const StringPrimitiveIr&) = delete;

	public:

		std::ostream& printType(std::ostream& out) const;

		const TypeIr& type() const { return TypeNameIr::instance; }
		const String& symbol() const { return _name; }
	};
}

#endif
