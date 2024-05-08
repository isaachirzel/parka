#ifndef PARKA_IR_CONVERSION_HPP
#define PARKA_IR_CONVERSION_HPP

#include "parka/ir/Type.hpp"

namespace parka::ir
{
	class ConversionIr
	{
		const Type& _from;
		const Type& _to;

	public:

		static ConversionIr entries[];
		static const usize entryCount;

	public:

		ConversionIr(const Type& from, const Type& to);

		const auto& to() const { return _to; }
		const auto& from() const { return _from; }
	};
}

#endif
