#ifndef PARKA_IR_CONVERSION_HPP
#define PARKA_IR_CONVERSION_HPP

#include "parka/ir/TypeIr.hpp"

namespace parka::ir
{
	struct ConversionIr
	{
		const bool _isIntrinsic;

		ConversionIr(bool isItrinsic):
			_isIntrinsic(isItrinsic)
		{}
		virtual ~ConversionIr() {}

		const auto& isIntrinsic() const { return _isIntrinsic; }
		virtual const TypeIr& to() const = 0;
		virtual const TypeIr& from() const = 0;
	};
}

#endif
