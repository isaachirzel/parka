#ifndef PARKA_IR_U64_PRIMITIVE_IR_HPP
#define PARKA_IR_U64_PRIMITIVE_IR_HPP

#include "parka/ir/EntityIr.hpp"
#include "parka/ir/InvalidTypeIr.hpp"

namespace parka::ir
{
	class U64PrimitiveIr: public TypeIr, public EntityIr
	{
		String _symbol;

	public:

		static U64PrimitiveIr instance;

	private:

		U64PrimitiveIr();
		U64PrimitiveIr(U64PrimitiveIr&&) = delete;
		U64PrimitiveIr(const U64PrimitiveIr&) = delete;

	public:

		std::ostream& printType(std::ostream& out) const;
		const String& symbol() const { return _symbol; }
		const TypeIr& type() const { return InvalidTypeIr::typeNameType; }
	};
}

#endif
