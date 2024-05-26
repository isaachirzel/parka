#ifndef PARKA_IR_CONVERSION_IR_HPP
#define PARKA_IR_CONVERSION_IR_HPP

#include "parka/ir/TypeIr.hpp"
#include "parka/validation/ConversionKey.hpp"
#include "parka/util/FlatMap.hpp"

namespace parka::ir
{
	class ConversionIr
	{
		const TypeIr& _to;
		const TypeIr& _from;

	public:

		static FlatMap<validation::ConversionKey, ConversionIr*> getIntrinsicConversions();

	public:

		ConversionIr(const TypeIr& to, const TypeIr& from);
		ConversionIr(ConversionIr&&) = default;
		ConversionIr(const ConversionIr&) = default;

		const TypeIr& to() const { return _to; }
		const TypeIr& from() const { return _from; }
	};
}

#endif
