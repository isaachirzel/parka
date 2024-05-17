#ifndef PARKA_IR_INTRINSIC_CONVERSION_IR_HPP
#define PARKA_IR_INTRINSIC_CONVERSION_IR_HPP

#include "parka/ir/ConversionIr.hpp"

namespace parka::ir
{
	class IntrinsicConversionIr: public ConversionIr
	{
		const TypeIr& _to;
		const TypeIr& _from;

	public:

		static IntrinsicConversionIr entries[];
		static const usize entryCount;

	public:

		IntrinsicConversionIr(const TypeIr& to, const TypeIr& from);
		IntrinsicConversionIr(IntrinsicConversionIr&&) = default;
		IntrinsicConversionIr(const IntrinsicConversionIr&) = delete;
		const TypeIr& to() const { return _to; }
		const TypeIr& from() const { return _from; }
	};
}

#endif
