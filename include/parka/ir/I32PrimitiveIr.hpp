#ifndef PARKA_IR_I32_PRIMITIVE_IR_HPP
#define PARKA_IR_I32_PRIMITIVE_IR_HPP

#include "parka/ir/EntityIr.hpp"
#include "parka/ir/InvalidTypeIr.hpp"

namespace parka::ir
{
	class I32PrimitiveIr: public TypeIr, public EntityIr
	{
		String _symbol;

	public:

		static I32PrimitiveIr instance;

	private:

		I32PrimitiveIr();
		I32PrimitiveIr(I32PrimitiveIr&&) = delete;
		I32PrimitiveIr(const I32PrimitiveIr&) = delete;

	public:

		std::ostream& printType(std::ostream& out) const;
		const String& symbol() const { return _symbol; }
		const TypeIr& type() const { return InvalidTypeIr::typeNameType; }
	};
}

#endif
