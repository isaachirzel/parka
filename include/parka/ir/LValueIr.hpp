#ifndef PARKA_IR_L_VALUE_HPP
#define PARKA_IR_L_VALUE_HPP

#include "parka/enum/ResolvableType.hpp"
#include "parka/ir/SymboledIr.hpp"
#include "parka/ir/TypedIr.hpp"

namespace parka::ir
{
	struct LValueIr: public SymboledIr, public TypedIr
	{
		const ResolvableType resolvableType;

		LValueIr(ResolvableType resolvableType):
			resolvableType(resolvableType)
		{}

		virtual ~LValueIr() {}
	};
}

#endif
