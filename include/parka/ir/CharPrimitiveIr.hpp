#ifndef PARKA_IR_CHAR_PRIMITIVE_IR_HPP
#define PARKA_IR_CHAR_PRIMITIVE_IR_HPP

#include "parka/ir/LValueIr.hpp"
#include "parka/ir/TypeIr.hpp"
#include "parka/ir/TypeNameIr.hpp"

namespace parka::ir
{
	class CharPrimitiveIr: public TypeIr, public LValueIr
	{
		String _symbol;

	public:

		static CharPrimitiveIr instance;

	private:

		CharPrimitiveIr();
		CharPrimitiveIr(CharPrimitiveIr&&) = default;
		CharPrimitiveIr(const CharPrimitiveIr&) = delete;

	public:

		std::ostream& printType(std::ostream& out) const;

		const TypeIr& type() const { return TypeNameIr::instance; }
		const String& symbol() const { return _symbol; }
	};
}

#endif
