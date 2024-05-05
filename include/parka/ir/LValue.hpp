#ifndef PARKA_IR_L_VALUE_HPP
#define PARKA_IR_L_VALUE_HPP

#include "parka/enum/ResolvableType.hpp"
#include "parka/ir/Symboled.hpp"
#include "parka/ir/Typed.hpp"

namespace parka::ir
{
	struct LValue: public Symboled, public Typed
	{
		const ResolvableType resolvableType;

		LValue(ResolvableType resolvableType):
			resolvableType(resolvableType)
		{}

		virtual ~LValue() {}
	};
}

#endif
