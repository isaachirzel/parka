#ifndef PARKA_IR_FLOAT_PRIMITIVE_IR_HPP
#define PARKA_IR_FLOAT_PRIMITIVE_IR_HPP

#include "parka/ir/TypeIr.hpp"
#include "parka/ir/InvalidTypeIr.hpp"

namespace parka::ir
{
	class FloatPrimitiveIr: public TypeIr
	{
	public:

		static FloatPrimitiveIr instance;

	private:

		FloatPrimitiveIr();
		FloatPrimitiveIr(FloatPrimitiveIr&&) = default;
		FloatPrimitiveIr(const FloatPrimitiveIr&) = delete;

	public:

		std::ostream& printType(std::ostream& out) const;

		const TypeIr& type() const { return InvalidTypeIr::typeNameType; }
	};
}

#endif
