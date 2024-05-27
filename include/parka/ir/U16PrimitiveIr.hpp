#ifndef PARKA_IR_U16_PRIMITIVE_IR_HPP
#define PARKA_IR_U16_PRIMITIVE_IR_HPP

#include "parka/ir/LValueIr.hpp"
#include "parka/ir/TypeNameIr.hpp"

namespace parka::ir
{
	class U16PrimitiveIr: public TypeIr, public LValueIr
	{
		String _symbol;

	public:

		static U16PrimitiveIr instance;

	private:

		U16PrimitiveIr();
		U16PrimitiveIr(U16PrimitiveIr&&) = delete;
		U16PrimitiveIr(const U16PrimitiveIr&) = delete;

	public:

		std::ostream& printType(std::ostream& out) const;
		const String& symbol() const { return _symbol; }
		const TypeIr& type() const { return TypeNameIr::instance; }
	};
}

#endif
