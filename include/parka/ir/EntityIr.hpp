#ifndef PARKA_IR_L_VALUE_HPP
#define PARKA_IR_L_VALUE_HPP

#include "parka/enum/EntityType.hpp"
#include "parka/ir/SymboledIr.hpp"
#include "parka/ir/TypedIr.hpp"

namespace parka::ir
{
	struct EntityIr: public SymboledIr, public TypedIr
	{
		const EntityType resolvableType;

		EntityIr(EntityType resolvableType):
			resolvableType(resolvableType)
		{}

		virtual ~EntityIr() {}
	};
}

#endif
