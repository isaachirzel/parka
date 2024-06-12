#include "parka/ir/CastIr.hpp"

namespace parka::ir
{
	CastIr::CastIr(const TypeIr& to, const TypeIr& from):
		_to(to),
		_from(from)
	{}
}
