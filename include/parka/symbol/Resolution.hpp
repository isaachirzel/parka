#ifndef PARKA_SYMBOL_RESOLUTION_HPP
#define PARKA_SYMBOL_RESOLUTION_HPP

#include "parka/enum/ResolvableType.hpp"
#include "parka/ir/ValueType.hpp"
#include "parka/util/String.hpp"

namespace parka
{
	struct Resolution
	{
		const ResolvableType resolvableType;

		Resolution(ResolvableType resolvableType) :
		resolvableType(resolvableType)
		{}
		virtual ~Resolution() {}

		virtual const String& symbol() const = 0;
		virtual const ir::ValueType *valueType() const = 0;
	};
}

#endif
