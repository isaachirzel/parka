#ifndef PARKA_IR_I8_PRIMITIVE_IR_HPP
#define PARKA_IR_I8_PRIMITIVE_IR_HPP

#include "parka/ir/EntityIr.hpp"
#include "parka/ir/InvalidTypeIr.hpp"

namespace parka::ir
{
	class I8PrimitiveIr: public TypeIr, public EntityIr
	{
		String _symbol;

	public:

		static I8PrimitiveIr instance;

	private:

		I8PrimitiveIr();
		I8PrimitiveIr(I8PrimitiveIr&&) = delete;
		I8PrimitiveIr(const I8PrimitiveIr&) = delete;

	public:

		std::ostream& printType(std::ostream& out) const;
		const String& symbol() const { return _symbol; }
		const TypeIr& type() const { return InvalidTypeIr::typeNameType; }
	};
}

#endif
