#ifndef PARKA_IR_INTRINSIC_CONVERSION_IR_HPP
#define PARKA_IR_INTRINSIC_CONVERSION_IR_HPP

#include "parka/ir/ConversionIr.hpp"

namespace parka::ir
{
	class IntrinsicConversionIr: public ConversionIr
	{
		const Type& _to;
		const Type& _from;

	public:

		static IntrinsicConversionIr entries[];
		static const usize entryCount;

	public:

		IntrinsicConversionIr(const Type& to, const Type& from);
		IntrinsicConversionIr(IntrinsicConversionIr&&) = default;
		IntrinsicConversionIr(const IntrinsicConversionIr&) = delete;

		const Type& to() const { return _to; }
		const Type& from() const { return _from; }
	};
}

#endif
