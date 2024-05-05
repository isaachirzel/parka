#ifndef PARKA_IR_TYPED_HPP
#define PARKA_IR_TYPED_HPP

#include "parka/ir/Type.hpp"

namespace parka::ir
{
	struct Typed
	{
		virtual ~Typed() {}
		virtual const Type& type() const =  0;
	};
}

#endif
