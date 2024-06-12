#ifndef PARKA_IR_CONVERSION_IR_HPP
#define PARKA_IR_CONVERSION_IR_HPP

#include "parka/ir/TypeIr.hpp"

namespace parka::ir
{
	class CastIr
	{
		const TypeIr& _to;
		const TypeIr& _from;

	public:

		CastIr(const TypeIr& to, const TypeIr& from);
		CastIr(CastIr&&) = default;
		CastIr(const CastIr&) = default;

		const TypeIr& to() const { return _to; }
		const TypeIr& from() const { return _from; }
	};
}

#endif
