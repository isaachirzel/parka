#ifndef PARKA_IR_U32_PRIMITIVE_IR_HPP
#define PARKA_IR_U32_PRIMITIVE_IR_HPP

#include "parka/ir/LValueIr.hpp"
#include "parka/ir/TypeNameIr.hpp"

namespace parka::ir
{
	class U32PrimitiveIr: public TypeIr, public LValueIr
	{
		String _symbol;

	public:

		static U32PrimitiveIr instance;

	private:

		U32PrimitiveIr();
		U32PrimitiveIr(U32PrimitiveIr&&) = delete;
		U32PrimitiveIr(const U32PrimitiveIr&) = delete;

	public:

		std::ostream& printType(std::ostream& out) const;
		const String& symbol() const { return _symbol; }
		const TypeIr& type() const { return TypeNameIr::instance; }
	};
}

#endif
