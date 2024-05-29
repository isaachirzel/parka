#ifndef PARKA_IR_VOID_PRIMITIVE_IR_HPP
#define PARKA_IR_VOID_PRIMITIVE_IR_HPP

#include "parka/ir/EntityIr.hpp"
#include "parka/ir/TypeIr.hpp"
#include "parka/ir/InvalidTypeIr.hpp"

namespace parka::ir
{
	class VoidPrimitiveIr: public TypeIr, public EntityIr
	{
		String _name;

	public:

		static VoidPrimitiveIr instance;

	private:

		VoidPrimitiveIr(const char *name);
		VoidPrimitiveIr(VoidPrimitiveIr&&) = default;
		VoidPrimitiveIr(const VoidPrimitiveIr&) = delete;

	public:

		std::ostream& printType(std::ostream& out) const;

		const TypeIr& type() const { return InvalidTypeIr::typeNameType; }
		const String& symbol() const { return _name; }
	};
}

#endif
