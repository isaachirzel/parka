#ifndef PARKA_IR_CONVERSION_IR_HPP
#define PARKA_IR_CONVERSION_IR_HPP

#include "parka/ir/TypeIr.hpp"

namespace parka::ir
{
	class ConversionIr
	{
		const TypeIr& _to;
		const TypeIr& _from;

	public:

		ConversionIr(const TypeIr& to, const TypeIr& from);
		ConversionIr(ConversionIr&&) = default;
		ConversionIr(const ConversionIr&) = default;

		const TypeIr& to() const { return _to; }
		const TypeIr& from() const { return _from; }
	};
}

#endif
